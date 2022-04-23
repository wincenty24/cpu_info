#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#include "threads.h"
#include "pitbull.h"
#include "values.h"

const int32_t max_watchdog_val = 10000;


bool compare_values(int32_t a, int32_t b){
    int32_t diff = a - b;
    uint32_t _abs = abs(diff);
    return (_abs > 2) ? false : true;
}

void set_zero(watchdog_t* des1, watchdog_t* des2)
{
    memset(des1, 0, sizeof(watchdog_t));
    memset(des2, 0, sizeof(watchdog_t));
}

void* waruj()
{
    while (!done)
    {
        watchdog_ref.read++;
        watchdog_ref.analyzer++;
        watchdog_ref.printer++;
        bool diff_read = compare_values(watchdog_val.read , watchdog_ref.read);
        bool diff_analyzer = compare_values(watchdog_val.analyzer, watchdog_ref.analyzer);
        bool diff_printer = compare_values(watchdog_val.printer, watchdog_ref.printer);
        bool fatal = diff_read & diff_analyzer & diff_printer;

       if(watchdog_ref.read > max_watchdog_val || watchdog_ref.analyzer > max_watchdog_val || watchdog_ref.printer > max_watchdog_val ||
       watchdog_val.read > max_watchdog_val || watchdog_val.analyzer > max_watchdog_val || watchdog_val.printer > max_watchdog_val){
           set_zero(&watchdog_ref, &watchdog_val);
       }
        if(!fatal){
            done = 1;
            printf("cos sie popsulo i nie bylo mnie slychac \n");
            free_memory(pre_ci, post_ci, saved_cpu_info, cpu_info);
            exit(-1);
        }
        sleep(1);
    }
    

}
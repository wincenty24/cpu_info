#include <sys/types.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "pitbull.h"
#include "values.h"

watchdog_t watchdog_ref = {0};
watchdog_t watchdog_val = {0};

volatile sig_atomic_t done = 0;
const watchdog_t watchdog_zero = {0};

bool compare_values(int32_t a, int32_t b){
    int32_t diff = a -b;
    uint32_t _abs = abs(diff);
    return (_abs > 2) ? false : true;

}

const int32_t max_watchdog_val = 10000;

void set_zero(watchdog_t* des1, watchdog_t* des2, watchdog_t* ref)
{
    des1 = ref;
    des2 = ref;
}
void term(int signum)
{
   printf("Caught!\n");
   done = 1;
}
void* waruj()
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    while (true)
    {

        //int t = sleep(1);
        /* sleep returns the number of seconds left if
         * interrupted */
        //while (t > 0)
        //{
        //    printf("Loop run was interrupted with %d "
        //           "sec to go, finishing...\n", t);
        //   // t = sleep(t);
       // }

        watchdog_ref.read++;
        watchdog_ref.analyzer++;
        watchdog_ref.printer++;


        bool diff_read = compare_values(watchdog_val.read , watchdog_ref.read);
        bool diff_analyzer = compare_values(watchdog_val.analyzer, watchdog_ref.analyzer);
        bool diff_printer = compare_values(watchdog_val.printer, watchdog_ref.printer);
        bool fatal = diff_read & diff_analyzer & diff_printer;
       /*
        ds++;
        if(ds> 15){
            watchdog_ref.read =0;
        }
        */

       if(watchdog_ref.read > max_watchdog_val || watchdog_ref.analyzer > max_watchdog_val || watchdog_ref.printer > max_watchdog_val ||
       watchdog_val.read > max_watchdog_val || watchdog_val.analyzer > max_watchdog_val || watchdog_val.printer > max_watchdog_val){
           set_zero(&watchdog_ref, &watchdog_val, &watchdog_zero);
       }

        if(!fatal){
            printf("cos sie popsulo i nie bylo mnie slychac \n");
            exit(1);

        }
        sleep(1);
    }
    

}
#include <sys/types.h>
#include <stdbool.h>

#include "reader.h"
#include "analyzer.h"


bool is_prepared_read = false;
bool is_prepared_anal = false;
bool is_prepared_printf = true;


void print_cpu(cpu_info_t* cpu_info, int32_t n_cpu){
    int idx;
    for(idx =0; idx < n_cpu; idx++){
        printf("cpu%d %f   ", idx, cpu_info->cpu_usage);
        cpu_info++;
    }
    printf("\n");
}

void *printer_thr_fun(int32_t n_cpu)
{
    while (true)
    {
        if(is_prepared_anal){
            print_cpu(cpu_info, n_cpu);
            is_prepared_anal = false;
            is_prepared_printf = true;
        }
        
        sleep(1);
    }
}

void *analyzer_thr_fun(int32_t n_cpu)
{
    while (true)
    {
        if(is_prepared_read)
        {
            pre_process(pre_ci, post_ci, saved_cpu_info, cpu_info, n_cpu);
            is_prepared_read = false;
            is_prepared_anal = true;
        }
        usleep(1000);
    }
}
void *reader_thr_fun(int32_t n_cpu)
{
    while (true)
    {
        if(is_prepared_printf){
            read_stat(pre_ci, n_cpu, "/proc/stat");
            is_prepared_anal = false;
            is_prepared_printf = false;
            is_prepared_read = true;
        }
        usleep(1000);
    }
}
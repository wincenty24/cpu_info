
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>


#include "lib/values.h"
#include "lib/reader.h"
#include "lib/analyzer.h"
#include "lib/cleaner.h"
#include "lib/pitbull.h"


void free_memory(){

    pthread_exit(NULL);
    free(pre_ci);
    free(post_ci);
    free(saved_cpu_info);
    free(cpu_info);
}

void stoper(int signum)
{
   done = 1;
   free_memory();
}


bool is_prepared_read = false;
bool is_prepared_anal = false;
bool is_prepared_printf = true;

void print_cpu(cpu_info_t* cpu_info, int32_t n_cpu){
    int idx;
    printf("\r ");
    for(idx =0; idx < n_cpu; idx++){
        printf("cpu%d %f   ", idx, cpu_info->cpu_usage);
        cpu_info++;
    }
    fflush(stdout);//kill 12233
}


void *printer_thr_fun(void* n_cpu_ptr)
{

    int32_t n_cpu = *(int32_t*)n_cpu_ptr;
    while (!done)
    {
        if(is_prepared_anal){
            print_cpu(cpu_info, n_cpu);
            watchdog_val.printer++;
            is_prepared_anal = false;
            is_prepared_printf = true;
        }
        
        sleep(1);
    }
}

void *analyzer_thr_fun(void* n_cpu_ptr)
{
    int32_t n_cpu = *(int32_t*)n_cpu_ptr;
    while (!done)
    {
        if(is_prepared_read)
        {
            pre_process(pre_ci, post_ci, saved_cpu_info, cpu_info, n_cpu);
            watchdog_val.analyzer++;
            is_prepared_read = false;
            is_prepared_anal = true;
        }
        usleep(1000);
    }
}

void *reader_thr_fun(void* n_cpu_ptr)
{
    int32_t n_cpu = *(int32_t*)n_cpu_ptr;
    while (!done)
    {
        if(is_prepared_printf){
            read_stat(pre_ci, n_cpu, "/proc/stat");
            watchdog_val.read++;
            is_prepared_anal = false;
            is_prepared_printf = false;
            is_prepared_read = true;
        }
        usleep(1000);
    }
}

int main(int argc, char **argv) {
    
    
    system("clear");
    done = 0;

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = stoper;
    sigaction(SIGTERM, &action, NULL);
    
    int pid = getpid();
    int parentID = getppid();

    printf("PID is %d  and Parent is %d \n",pid, parentID);

    n_cpus = get_nprocs() + 1;

    pre_ci = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * n_cpus);
    post_ci = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    saved_cpu_info = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    cpu_info = (cpu_info_t*)malloc(sizeof(cpu_info_t) * n_cpus);
    
    reset_post_cpu_info_t(saved_cpu_info, n_cpus);
    reset_post_cpu_info_t(post_ci, n_cpus);

    pthread_t reader_thr;
    pthread_t analyzer_thr;
    pthread_t printer_thr;
    pthread_t watchdog_thr; 

    pthread_create(&reader_thr, NULL, reader_thr_fun, (void*)&n_cpus);
    pthread_create(&analyzer_thr, NULL, analyzer_thr_fun, (void*)&n_cpus);
    pthread_create(&printer_thr, NULL, printer_thr_fun, (void*)&n_cpus);
    pthread_create(&watchdog_thr, NULL, waruj, NULL);

    free_memory();

    return 0;    
    //kill 10405
}

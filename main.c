
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

#include "lib/reader.h"
#include "lib/analyzer.h"
#include "lib/cleaner.h"
#include "lib/pitbull.h"
#include "lib/values.h"
#include "lib/threads.h"



bool is_prepared_read = false;
bool is_prepared_anal = false;
bool is_prepared_printf = true;

void stoper()
{
   done = 1;
   free_memory(pre_ci, post_ci, saved_cpu_info, cpu_info);
   exit(0);
}

void print_cpu(cpu_info_t* cpu_info, int32_t n_cpu){
    int idx;
    printf("\r ");
    for(idx =0; idx < n_cpu; idx++){
        printf("cpu%d %f   ", idx, cpu_info->cpu_usage);
        cpu_info++;
    }
    fflush(stdout);
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
void setup(int32_t arg, char* name){
    int32_t result = system("clear");
    if(result == -1){
        printf("cleaning error");
    }
    set_zero(&watchdog_ref, &watchdog_val);

    done = 0;
	printf("%d program's name is: %s\n",arg, name);
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = stoper;
    sigaction(SIGTERM, &action, NULL);
    
    int32_t pid = getpid();
    printf("PID %d \n", pid);
    n_cpus = get_nprocs() + 1;
}
int main(int argc, char **argv) {
    
    setup(argc, argv[0]);
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
    pthread_exit(NULL);

   
    free_memory(pre_ci, post_ci, saved_cpu_info, cpu_info);

    return 0;    
}

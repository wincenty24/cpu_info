
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "lib/values.h"
#include "lib/reader.h"
#include "lib/analyzer.h"
#include "lib/cleaner.h"

/*
void clear_pre_cpu_info_t(pre_cpu_info_t* cpi){
        int idx;
    for(idx =0; idx < n_cpu; idx++){
        memset(cpi->pre_cpu_str, 0, sizeof(pre_cpu_info_t));
        cpi->pre_cpu_str=0;
    }
}
*/
void print_cpu(cpu_info_t* cpu_info, int32_t n_cpu){
    int idx;
    for(idx =0; idx < n_cpu; idx++){
        printf("cpu%d %f   ", idx, cpu_info->cpu_usage);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    n_cpus = get_nprocs() + 1;

    pre_cpu_info_t* pre_ci = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * n_cpus);
    post_cpu_info_t* post_ci = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    post_cpu_info_t* saved_cpu_info = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);

    cpu_info_t* cpu_info = (cpu_info_t*)malloc(sizeof(cpu_info_t) * n_cpus);
    
    reset_post_cpu_info_t(saved_cpu_info, n_cpus);
    reset_post_cpu_info_t(post_ci, n_cpus);

    pthread_t Reader_thr;
    

    //get_nprocs_conf(), get_nprocs());

    int idx;
    for(idx =0; idx<10;idx++){
        
        
        read_stat(pre_ci, n_cpus, "/proc/stat");

        pre_process(pre_ci, post_ci, saved_cpu_info, cpu_info, n_cpus);
        
        print_cpu(cpu_info, n_cpus);
        sleep(1);
        
     
    }

    free(pre_ci);
    free(post_ci);
    free(saved_cpu_info);
    free(cpu_info);
    return 0;    
    
}


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysinfo.h>

#include "lib/values.h"
#include "lib/reader.h"




int main(int argc, char **argv) {
    n_cpus = 8 + 1;

    pre_cpu_info_t* pre_ci = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * n_cpus);
    post_cpu_info_t* post_ci = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    

    //get_nprocs_conf(), get_nprocs());
    read_stat(pre_ci, n_cpus, "/proc/stat");

    free(pre_ci);
    free(post_ci);
    return 0;    
    
    }

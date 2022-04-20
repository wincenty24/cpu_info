#ifndef VALUES_H
#define VALUES_H
#include "stdint.h"

#define max_size_of_line 1024
//const

//global
uint32_t n_cpus;

typedef struct pre_cpu_info_t{
    char pre_cpu_str[max_size_of_line];
} pre_cpu_info_t;

typedef struct post_cpu_info_t
{
    uint64_t user;
    uint64_t nice;
    uint64_t system;
    uint64_t idle;
    uint64_t iowait;
    uint64_t irq;
    uint64_t softirq;
    uint64_t steal;
    uint64_t guest;
} post_cpu_info_t;


#endif
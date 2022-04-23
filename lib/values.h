#ifndef VALUES_H
#define VALUES_H

#include <unistd.h>
#include <signal.h>

#include "stdint.h"

#define max_size_of_line 1024
//const

//global
uint32_t n_cpus;

volatile sig_atomic_t done;

typedef struct pre_cpu_info_t{
    char pre_cpu_str[max_size_of_line];
    int32_t siezof_line;
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
    uint64_t guest_nice;
} post_cpu_info_t;

typedef struct cpu_info_t
{
    float cpu_usage;
}cpu_info_t;

 pre_cpu_info_t* pre_ci;
 post_cpu_info_t* post_ci;
 post_cpu_info_t* saved_cpu_info;
 cpu_info_t* cpu_info;

typedef struct watchdog_t
{
    int32_t read;
    int32_t analyzer;
    int32_t printer;
}watchdog_t;

#endif
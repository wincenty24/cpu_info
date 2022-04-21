#ifndef ANALYZER_H
#define ANALYZER_H

#include "stdint.h"
#include "values.h"

void pre_process(pre_cpu_info_t* pre_ci, post_cpu_info_t* post_ci, post_cpu_info_t* saved_cpu_info, cpu_info_t* cpu_info, int32_t n_cpus);

#endif
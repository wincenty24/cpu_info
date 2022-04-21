#ifndef CLEANER_H
#define CLEANER_H
#include <sys/types.h>

#include "values.h"

void reset_post_cpu_info_t(post_cpu_info_t* saved_cpu_info, int32_t n_cpu);
void reset_pre_cpu_info_t(pre_cpu_info_t* pci);

#endif
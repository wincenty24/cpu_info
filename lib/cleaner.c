#include <sys/types.h>
#include <string.h>

#include "values.h"

void reset_post_cpu_info_t(post_cpu_info_t* pci, int32_t n_cpu)
{
    memset(pci, 0, sizeof(post_cpu_info_t) * n_cpus);
}

void reset_pre_cpu_info_t(pre_cpu_info_t* pci)
{
    memset(pci->pre_cpu_str, '\0', sizeof(char) * max_size_of_line);
    pci->siezof_line = 0;
}
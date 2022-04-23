#include <sys/types.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "values.h"

void free_memory(pre_cpu_info_t *a, post_cpu_info_t *b, post_cpu_info_t *c, cpu_info_t *d ){
    free(a);
    free(b);
    free(c);
    free(d);
}

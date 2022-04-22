#ifndef THREADS_H
#define THREADS_H

#include <sys/types.h>

void *printer_thr_fun(int32_t n_cpu);
void *analyzer_thr_fun(int32_t n_cpu);
void *reader_thr_fun(int32_t n_cpu);

#endif
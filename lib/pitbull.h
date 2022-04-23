#ifndef PITBULL_H
#define PITBULL_H

#include "values.h"

watchdog_t watchdog_ref;
watchdog_t watchdog_val;

void set_zero(watchdog_t* des1, watchdog_t* des2);
bool compare_values(int32_t a, int32_t b);
void* waruj();

#endif
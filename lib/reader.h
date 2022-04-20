#ifndef READER_H
#define READER_H

#include "stdint.h"
#include <stdio.h>
#include "values.h"

void read_stat(struct pre_cpu_info_t* pci, int32_t lines2read, char* file_name);

#endif

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#include "values.h"
#include "reader.h"
#include "cleaner.h"

void read_stat(pre_cpu_info_t* pci, int32_t lines2read, char* file_name)
{
    FILE* file;
    int32_t idx;
    char* line = NULL;
    size_t len = 0;
    ssize_t sizeof_line;
    file = fopen(file_name,"r");
    for(idx = 0; idx < lines2read; idx++){    
        reset_pre_cpu_info_t(pci); 
        sizeof_line = getline(&line, &len, file);
        pci->siezof_line = sizeof_line;
        strncpy(pci->pre_cpu_str, line, sizeof_line);
        pci++;//arytmetyka wskaźników, przejście do następnej struktury
    }
    free(line);
    fclose(file);
}
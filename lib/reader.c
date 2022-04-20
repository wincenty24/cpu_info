#include "values.h"
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include "reader.h"

void read_stat(pre_cpu_info_t* pci, int32_t lines2read, char* file_name)
{
    FILE* file;
    int idx;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    file = fopen(file_name,"r");
    for(idx = 0; idx < lines2read; idx++){     
        read = getline(&line, &len, file);
        strncpy(pci->pre_cpu_str, line, read);
        pci++;//arytmetyka wskaźników, przejście do następnej struktury
    }
    fclose(file);
}
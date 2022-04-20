#include <gtest/gtest.h>
#include "stdint.h"

extern "C"
{
#include "../lib/values.h"
#include "../lib/reader.h"
}

void prepare_ref(pre_cpu_info_t* pci, int32_t* sizeof_line){
    strncpy(pci->pre_cpu_str, "cpu  2755122 14745 784029 25734029 25009 0 329582 0 0 0\n", sizeof_line[0]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu0 334925 2902 105896 5789041 5595 0 132040 0 0 0\n", sizeof_line[1]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu1 340210 2534 93689 2865506 2629 0 100177 0 0 0\n", sizeof_line[2]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu2 346537 2132 94696 2861357 2607 0 45320 0 0 0\n", sizeof_line[3]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu3 352168 1497 98172 2841324 3073 0 21932 0 0 0\n", sizeof_line[4]);
    pci++;    
    strncpy(pci->pre_cpu_str, "cpu4 345802 1149 96143 2860222 2658 0 12643 0 0 0\n", sizeof_line[5]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu5 345285 914 96775 2861577 2624 0 6496 0 0 0\n", sizeof_line[6]);
    pci++;
    strncpy(pci->pre_cpu_str, "cpu6 347014 1888 94305 2800465 3054 0 5282 0 0 0\n", sizeof_line[7]);
    pci++;   
    strncpy(pci->pre_cpu_str, "cpu7 343178 1728 104350 2854533 2767 0 5690 0 0 0\n", sizeof_line[8]);    
}
void compare_char(char* a, char* b, int32_t sizeof_line){
    int32_t are_eq = strncmp(a, b, sizeof_line);
    ASSERT_FALSE(are_eq);
}

void compare_pre_cpu_info_t(pre_cpu_info_t* pci, pre_cpu_info_t* pci_ref, int32_t n_pre_cpu_info_t, int32_t* sizeof_line){
    for(int32_t i =0; i < n_pre_cpu_info_t; i++){
        compare_char(pci_ref->pre_cpu_str, pci->pre_cpu_str, sizeof_line[i]);
        pci++;
        pci_ref++;
    }
}
TEST(READER,read_stat ){
    const int32_t nproc = 9;
    int32_t sizeof_line[9] = {56, 52, 51, 50, 50, 50, 48, 49, 50};
    pre_cpu_info_t* pci = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * nproc);
    pre_cpu_info_t* pci_ref = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * nproc);
    char file_name[] = "../test/proc_info.txt";
    
    read_stat(pci, nproc, file_name);
    prepare_ref(pci_ref, sizeof_line);
    compare_pre_cpu_info_t(pci, pci_ref, nproc, sizeof_line);
    
    free(pci);
    free(pci_ref);
}

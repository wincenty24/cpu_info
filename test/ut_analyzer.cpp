#include <gtest/gtest.h>
#include "stdint.h"
#include <stdio.h>

extern "C"
{
#include "../lib/analyzer.h"
}

void set_ref_test(post_cpu_info_t* pci){
     pci->user=2755122;
     pci->nice=14745;
     pci->system=784029;
     pci->idle=25734029;
     pci->iowait=25009;
     pci->irq=0;
     pci->softirq=329582;
     pci->steal=0;
     pci->guest=0;
     pci->guest_nice=0;
}

void compare_test(post_cpu_info_t pci_result, post_cpu_info_t pci_ref)
{
    const int32_t n_elem_in_post_cpu_info_t = 10;

    uint64_t result_val[n_elem_in_post_cpu_info_t] = {pci_result.user, pci_result.nice, pci_result.system, pci_result.idle, pci_result.iowait, pci_result.irq, pci_result.softirq, pci_result.steal, pci_result.guest, pci_result.guest_nice};
    uint64_t ref_val[n_elem_in_post_cpu_info_t] = {pci_ref.user, pci_ref.nice, pci_ref.system, pci_ref.idle, pci_ref.iowait, pci_ref.irq, pci_ref.softirq, pci_ref.steal, pci_ref.guest, pci_ref.guest_nice};

    for(int32_t i =0; i< n_elem_in_post_cpu_info_t; i++){
        EXPECT_EQ(result_val[i], ref_val[i]);
    }
}

TEST(analyzer, splitter_test){
    
    const int32_t n_cpu = 1;

    pre_cpu_info_t pre_ci_input;
    post_cpu_info_t post_ci_res;
    post_cpu_info_t post_ci_ref;
    set_ref_test(&post_ci_ref);

    char data[] = "cpu  2755122 14745 784029 25734029 25009 0 329582 0 0 0\n";
    int32_t data_len = strlen(data);
    memcpy(pre_ci_input.pre_cpu_str, data, sizeof(data));
    pre_ci_input.siezof_line = data_len;

    splitter(pre_ci_input.pre_cpu_str, &post_ci_res);
    compare_test(post_ci_res, post_ci_ref);
}
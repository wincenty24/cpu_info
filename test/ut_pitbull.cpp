#include <gtest/gtest.h>
#include <cstdlib>
#include <pthread.h>
#include <iostream>
extern "C"
{
#include "../lib/pitbull.h"
}

TEST(pitbull, compare_values_true_test)
{
    bool res = compare_values(1,1);
    ASSERT_EQ(1, res);
        
}

TEST(pitbull, compare_values_false_test)
{
    bool res = compare_values(100, 32);
    ASSERT_EQ(0, res);
        
}
void compare_watchdogs(watchdog_t a, watchdog_t b){
    const int n_elem_in_watchdog = 3;
    int32_t res[3] = {a.analyzer, a.read, a.printer};
    int32_t ref[3] = {b.analyzer, b.read, b.printer};
    for(int i = 0; i< n_elem_in_watchdog; i++){
        EXPECT_EQ(res[i], ref[i]);
    }

}
TEST(pitbull, set_zero_test)
{
    watchdog_t a;
    watchdog_t b;
    watchdog_t ref = {0};
    set_zero(&a, &b);
    compare_watchdogs(a, ref);
    compare_watchdogs(b, ref);
}

TEST(pitbull, waruj_fail_test)
{
    set_zero(&watchdog_ref, &watchdog_val);
    done = 0;
    n_cpus = 3;
    pre_ci = (pre_cpu_info_t*)malloc(sizeof(pre_cpu_info_t) * n_cpus);
    post_ci = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    saved_cpu_info = (post_cpu_info_t*)malloc(sizeof(post_cpu_info_t) * n_cpus);
    cpu_info = (cpu_info_t*)malloc(sizeof(cpu_info_t) * n_cpus);

    watchdog_val.analyzer+=5;
    watchdog_val.printer+=6;
    watchdog_val.printer+=7;
    testing::internal::CaptureStdout();
    waruj();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "cos sie popsulo i nie bylo mnie slychac \n");    
    EXPECT_EQ(done, 1);

}
#include "reader.h"
#include "values.h"

#include <string.h>
#include <stdlib.h>

void put(int32_t idx, char* input, post_cpu_info_t* post_ci){    
    if(idx > 0){
        uint64_t transformed_val = atoi(input);
        //uint64_t* ptr[10] = {post_ci->user};
        switch (idx)
        {
        case 1:
            post_ci->user = transformed_val;
        break;
        case 2:
            post_ci->nice = transformed_val;
        break;
        case 3:
            post_ci->system = transformed_val;
        break;
        case 4:
            post_ci->idle = transformed_val;
        break;
        case 5:
            post_ci->iowait = transformed_val;
        break;
        case 6:
            post_ci->irq = transformed_val;
        break;
        case 7:
            post_ci->softirq = transformed_val;
        break;
        case 8:
            post_ci->steal = transformed_val;
        break;
        case 9:
            post_ci->guest = transformed_val;
        case 10:
            post_ci->guest_nice = transformed_val;
        break;
        }
    }
}

void splitter(char* input, post_cpu_info_t* post_ci)
{
    char split_char[] = " ";
    char *word = strtok(input, split_char);
    int i = 0;
	
    while (word != NULL)
	{
        put(i, word, post_ci);
		word = strtok(NULL, split_char);
	    i++;
    }
}

float calculate_cpu_usage(post_cpu_info_t* post_ci, post_cpu_info_t* saved_cpu_info){
    uint64_t PrevIdle = saved_cpu_info->idle + saved_cpu_info->iowait;
    uint64_t Idle = post_ci->idle + post_ci->iowait;

    uint64_t PrevNonIdle = saved_cpu_info->user +  saved_cpu_info->nice + saved_cpu_info->system + saved_cpu_info->irq + saved_cpu_info->softirq + saved_cpu_info->steal;
    uint64_t NonIdle = post_ci->user +  post_ci->nice + post_ci->system + post_ci->irq + post_ci->softirq + post_ci->steal;

    uint64_t PrevTotal = PrevIdle + PrevNonIdle;
    uint64_t Total = Idle + NonIdle;

    int64_t totald = Total - PrevTotal;
    int64_t idled = Idle - PrevIdle;

    float part1 = (totald - idled);
    float part2 = totald;
    float CPU_Percentage = part1/part2*(float)100;

    return CPU_Percentage;
}
void save(post_cpu_info_t* post_ci, post_cpu_info_t* saved_cpu_info)
{
    memcpy(saved_cpu_info, post_ci, sizeof(post_cpu_info_t));
}

void pre_process(pre_cpu_info_t* pre_ci, post_cpu_info_t* post_ci, post_cpu_info_t* saved_cpu_info, cpu_info_t* cpu_info, int32_t n_cpus)
{
    int32_t idx;
    for(idx = 0; idx < n_cpus; idx++){
        splitter(pre_ci->pre_cpu_str, post_ci);
        float cpu_usage = calculate_cpu_usage(post_ci, saved_cpu_info);
        cpu_info->cpu_usage = cpu_usage;
        save(post_ci, saved_cpu_info);
        pre_ci++;
        post_ci++;
        saved_cpu_info++;
        cpu_info++;
    }
}
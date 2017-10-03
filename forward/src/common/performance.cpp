
#include "performance.h"

#include <string.h>

#include <iostream>

using namespace std;

Performance::Performance()
{
    memset(&performance_data_,0,sizeof(performance_data_));
}

void Performance::PerformanceCount(int data_size)
{
    performance_data_.forward_count_now++;
    if(performance_data_.forward_count_now - performance_data_.forward_count_last > 10000)
    {
        struct timeval temp_time;
        gettimeofday(&temp_time,0);
        double time_diff = temp_time.tv_sec-performance_data_.time.tv_sec
            +(temp_time.tv_usec-performance_data_.time.tv_usec)/1000000.0;
        if(time_diff >= 1.0)                                                        
        {   
            int forward_num = (performance_data_.forward_count_now-
                performance_data_.forward_count_last)/time_diff;  
            int forward_data_size = forward_num * data_size / 1000;      
            cout << forward_num << ", " 
                 << forward_data_size  << "KB/s"    
                << endl;                                                            
            performance_data_.forward_count_last = performance_data_.forward_count_now;        
            performance_data_.time.tv_sec = temp_time.tv_sec;       
            performance_data_.time.tv_usec = temp_time.tv_usec;     
        }
    }        
}

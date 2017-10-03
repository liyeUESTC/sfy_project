#ifndef FORWARD_COMMON_PERFORMANCE_H_
#define FORWARD_COMMON_PERFORMANCE_H_

#include <sys/time.h>

struct PerformanceData
{

	int forward_count_last;
	int forward_count_now;
	struct timeval time;
};
class Performance
{
public:
    Performance();
    ~Performance() {};
    void PerformanceCount(int data_size);
private:
    struct PerformanceData performance_data_;

};

#endif //FORWARD_COMMON_PERFORMANCE_H_


#include <stdlib.h>

#include <vector>
#include <iostream>

#include "base_define.h"

class RadarPulse
{
public:
    RadarPulse(struct PulseGenerateWord pgw);
    ~RadarPulse() {};
    int Generate();
    std::vector<struct PulseDescribeWord> &pdw_vec()
    {
        return pdw_vec_;
    }
private:
    struct PulseGenerateWord pgw_;
    std::vector<struct PulseDescribeWord> pdw_vec_;
};

template <typename T>
T Random(T start,T end)
{
    return start + (end-start)*rand()/(RAND_MAX + 1.0);

}

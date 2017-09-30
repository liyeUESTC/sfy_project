#ifndef GRADUATION_SRC_COMMON_ALGORITHM_H_
#define GRADUATION_SRC_COMMON_ALGORITHM_H_

#include <vector>

#include "base_define.h"

class Algorithm
{
public:
    Algorithm(const std::vector<struct PulseDescribeWord> &pdw_vec)
        :pdw_vec_(pdw_vec)
    {}
    virtual ~Algorithm() {}
    virtual int Run() = 0;
    std::vector<struct RadarData> & radar_data_vec()
    {
        return radar_data_vec_;
    }
protected:
    std::vector<struct PulseDescribeWord>pdw_vec_;
    std::vector<struct RadarData> radar_data_vec_;
private:

};
#endif // GRADUATION_SRC_COMMON_ALGORITHM_H_

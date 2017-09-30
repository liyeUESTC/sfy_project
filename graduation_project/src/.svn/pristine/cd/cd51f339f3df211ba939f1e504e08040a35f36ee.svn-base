#ifndef GRADUATION_SRC_COMMON_CDIFALGORITHM_H_
#define GRADUATION_SRC_COMMON_CDIFALGORITHM_H_

#include <vector>
#include <list>

#include "algorithm.h"
#include "base_define.h"

// CDIF algorithm
// usage:
// CDIFAlgorithm cdif_algorithm(pdw_vec,kCDIFPercentParam);
//cdif_algorithm.Run();
//
class CDIFAlgorithm:public Algorithm
{
public:
    CDIFAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
                    double sample_time,double percent_param);
    ~CDIFAlgorithm() {}

    //Run cdif algorithm
    int Run();
    //return radar data
private:
    //use pri_vec detection pdw from pdw_vec
    int PDWDetection(const std::vector<double> &pri_vec);
    double percent_param_;
    double sample_time_;
};

//求绝对值函数
template <typename T>
T abs(T num)
{
    if(num < 0)
        num = -num;
    return num;
}

#endif //GRADUATION_SRC_COMMON_CDIFALGORITHM_H_

#ifndef GRADUATION_SRC_COMMON_SDIFALGORITHM_H_
#define GRADUATION_SRC_COMMON_SDIFALGORITHM_H_

#include <vector>

#include "algorithm.h"
#include "base_define.h"

class SDIFAlgorithm:public Algorithm
{
public:
    SDIFAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
            double sample_time,int pulse_sum,
            double sdif_param1,double sdif_param2);
    ~SDIFAlgorithm() {}
    int Run();
private:
    std::vector<double> HistogramCalculate(int level) const;
    std::vector<double> &SubharmonicCheck(std::vector<double> &pri_vec) const;
    std::vector<double> PriMeasure(int level) const;
    int PDWDetection(const std::vector<double> &pri_vec);
    double sdif_param1_;
    double sdif_param2_;
    double sample_time_;
    int pulse_sum_;
};
#endif // GRADUATION_SRC_COMMON_SDIFALGORITHM_H_

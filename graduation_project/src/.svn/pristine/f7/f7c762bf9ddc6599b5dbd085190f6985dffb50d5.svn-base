#ifndef GRADUATION_SRC_COMMON_PRIALGORITHM_H_
#define GRADUATION_SRC_COMMON_PRIALGORITHM_H_

#include <vector>

#include "algorithm.h"
#include "base_define.h"

class PRIAlgorithm:public Algorithm
{
public:
    struct Pri
    {
        Pri():data1(0.0),data2(0.0),num(0) 
        {}
        Pri(const struct Pri &pri)
        {
            data1 = pri.data1;
            data2 = pri.data2;
            num = pri.num;
        }
        ~Pri()
        {}
        double data1;
        double data2;
        int num;
    };
	PRIAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
				double sample_time,double pri_param1,
				double pri_param2,double pri_param3);
	~PRIAlgorithm() {}
	int Run();
private:
	std::vector<double> PriMeasure() const;
	int PdwDetection(const std::vector<double> &pri_vec);
	double pri_param1_;
	double pri_param2_;
	double pri_param3_;
	double sample_time_;
};
#endif   //GRADUATION_SRC_COMMON_PRIALGORITHM_H_

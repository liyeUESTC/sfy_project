#ifndef GRADUATION_PROJECT_SRC_COMMON_H_
#define GRADUATION_PROJECT_SRC_COMMON_H_

#include <vector>
#include <sstream>
#define FAILED -1
#define SUCCESSFUL 1

const double kMathConstantE = 2.718281828;
const double kMathConstantPi = 3.141592653;

struct PulseGenerateWord
{
    double doa; //到达角 0-360 
    double rf; //载频 0GHZ-20GHZ 
    double pw; //脉宽 0us-200us
    double  pa; //脉幅 0.5v-4.5v
    double pri;  //100us-10ms us
    double time_length; //ms
};

struct PulseDescribeWord
{
    double doa;  //脉冲到达方向 0-360
    double rf;     //载频 1GHZ-20GHZ
    double pw;     //脉宽 0.1us-1000us
    double pa;     //脉幅 
    double toa;    //到达时间  PRI 50us-5ms
};

struct RadarData
{
    double pri;
    std::vector<struct PulseDescribeWord> pdw_vec;
};

template <typename T>
T StrTo(const std::string &str)
{
    std::istringstream iss(str);
    T target;
    iss >> target;
    return target;
}

template <typename T>
std::string ToStr(T param)
{
    std::ostringstream oss;
    oss << param;
    std::string str;
    str = oss.str();
    return str;
}

template <typename T>
T MyMax(T param1,T param2)
{
    return (param1 > param2)?param1:param2;
} 

//雷达生成参数
const double kToaRandomError = 0.0; //到达时间误差
const double kLoseProbability = 0.0;  //脉冲丢失概率
//聚类分选参数
const double kMinDoa = 0.0;  //°
const double kMaxDoa = 360.0;  
const double kMinRf = 0.0;  //GHZ
const double kMaxRf = 20.0;
const double kMinPw = 0.0;
const double kMaxPw = 200;  //us
const double kDensityThreshold = 0.5;

//CDIF param
const int kCDIFMaxOrder = 6;  //最大的直方图差值阶数
const double kCDIFToleranceRange = 0.04;  //容差范围
const double kCDIFMaxToleranceValue = 1.0+kCDIFToleranceRange;
const double kCDIFMinToleranceValue = 1.0-kCDIFToleranceRange;
const double kCDIFParam = 0.6;

//SDIF param
const int kSDIFMaxOrder = 6;   //SDIF最大的直方图差值阶数
const double kSDIFToleranceRange = 0.04;  //容差范围
const double kSDIFMaxToleranceValue = 1.0 + kSDIFToleranceRange;
const double kSDIFMinToleranceValue = 1.0 - kSDIFToleranceRange;
const double kSDIFParam1 = 0.5;
const double kSDIFParam2 = 0.8;

//PRI param
const int kPRIIntervalNum = 200;
const double kPRIMinPriValue = 0.0;  //ms
const double kPRIMaxPriValue = 10.0;   //ms
const double kPRIIntervalWidth = (kPRIMaxPriValue-kPRIMinPriValue) /
                                 (double)kPRIIntervalNum;
const double kPRIToleranceRange = 0.01;
const double kPRIMaxToleranceValue = 1.0 + kPRIToleranceRange;
const double kPRIMinToleranceValue = 1.0 - kPRIToleranceRange;
const double kPRIParam1 = 0.7;
const double kPRIParam2 = 0.7;
const double kPRIParam3 = 0.7;
#endif // GRADUATION_PROJECT_SRC_COMMON_H_



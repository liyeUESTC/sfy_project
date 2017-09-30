#include "radar_pulse.h"

RadarPulse::RadarPulse(struct PulseGenerateWord pgw)
{
    pgw_ = pgw;
}

int RadarPulse::Generate()
{
    double start_time = Random(0.0,pgw_.pri);
    while(start_time < pgw_.time_length)
    {
        struct PulseDescribeWord pulse_describe_word;
        pulse_describe_word.doa = pgw_.doa;
        pulse_describe_word.rf = pgw_.rf;
        pulse_describe_word.pw = pgw_.pw;
        pulse_describe_word.pa = pgw_.pa;

        //到达时间加上随机误差
        pulse_describe_word.toa = start_time;

        //模拟脉冲丢失
        double random = Random(0.0,1.0);
        if(random > kLoseProbability)
            pdw_vec_.push_back(pulse_describe_word);

        start_time += Random((1-kToaRandomError)*pgw_.pri,(1+kToaRandomError)*pgw_.pri); 
    }

    return SUCCESSFUL;
}

#ifndef GRADUATIONPROJECT_SRC_COMMON_RADARPULSEMANAGER_H_
#define GRADUATIONPROJECT_SRC_COMMON_RADARPULSEMANAGER_H_

#include <vector>
#include <string>
#include <fstream>

#include "singleton.h"
#include "base_define.h"

class RadarPulseManager:public Singleton<RadarPulseManager>
{
public:
    RadarPulseManager() {};
    ~RadarPulseManager(){};
    int Init(const char *file_name);
    int Generate();
    std::vector<struct PulseDescribeWord>& pdw_vec()
    {
        return pdw_vec_;
    }
private:
    int ReadParam(std::ifstream &input);
    int InitParam(const std::string &param_str);
    std::vector<struct PulseGenerateWord> pgw_vec_;
    std::vector<struct PulseDescribeWord> pdw_vec_;
};



bool IsSmall(const struct PulseDescribeWord &pdw1,const struct PulseDescribeWord &pdw2);
#endif // GRADUATIONPROJECT_SRC_COMMON_RADARPULSEMANAGER_H_

/*************************************************************************
	> File Name: critical_area.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月10日 星期五 10时47分07秒
    > Function:对mutex进一步封装 减少使用步骤 
 ************************************************************************/

#ifndef CRITICAL_AREA_H_
#define CRITICAL_AREA_H_

#include "mutex.h"

class CriticalArea
{
public:
    CriticalArea();
    ~CriticalArea();
    CriticalArea(const CriticalArea &) = delete;
    CriticalArea &operator=(const CriticalArea &) = delete;
private:
    Mutex mutex_;
};
#endif

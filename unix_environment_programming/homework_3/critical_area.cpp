/*************************************************************************
	> File Name: critical_area.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月10日 星期五 10时50分29秒
    > Function: 
 ************************************************************************/

#include "critical_area.h"

CriticalArea::CriticalArea()
{
    ReturnStatus rec = mutex.Lock();
    if(-1 == rec.return_value())
    {
        std::cout << "CriticalArea structure function error" << std::endl;
        throw "CriticalArea structure function error" ;
    }
}

CriticalArea::~CriticalArea()
{
    ReturnStatus rec = mutex.Unlock()
    if(-1 == rec.return_value())
    {
        std::cout << "CriticalArea destructure function error" << std::endl;
        throw "CriticalArea destructure function error" ;
    }
}

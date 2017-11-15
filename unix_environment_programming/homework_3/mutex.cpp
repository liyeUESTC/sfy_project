/*************************************************************************
	> File Name: mutex.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月10日 星期五 10时26分28秒
    > Function: 
 ************************************************************************/

#include "mutex.h"

#include <iostream>

Mutex::Mutex()
{
    int rec = pthread_mutex_init(&mutex_,nullptr);
    if(0 != rec)
    {
        std::cout << "structure function error" << std::endl;
        throw "pthread_mutex_init error";
    }
}

Mutex::~Mutex()
{
    int rec = pthread_mutex_destroy(&mutex_);
    if(0 != rec)
    {
        std::cout << "destructure function error" << std::endl;
        throw "pthread_mutex_destory error";
    }
}

ReturnStatus Mutex::Lock()
{
    int rec = pthread_mutex_lock(&mutex_);
    if(0 != rec)
    {
        return ReturnStatus(-1,rec);
    }
}

ReturnStatus Mutex::TryLock()
{
    int rec = pthread_mutex_trylock(&mutex_);
    if(0 != rec)
        return ReturnStatus(-1,rec);
}

ReturnStatus Mutex::Unlock()
{
    int rec = pthread_mutex_unlock(&mutex_);
    if(0 != rec)
        return ReturnStatus(-1,rec);
}

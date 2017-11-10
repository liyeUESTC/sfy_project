/*************************************************************************
	> File Name: mutex.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月10日 星期五 10时17分31秒
    > Function:封装linux互斥量 
 ************************************************************************/

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

#include "return_status.h"

class Mutex
{
public:
    Mutex();
    ~Mutex();
    ReturnStatus Lock();
    ReturnStatus TryLock();
    ReturnStatus Unlock();

    Mutex(const Mutex &) = delete;
    Mutex &operator=() = delete;
private:
    pthread_mutex_t mutex_;
};
#endif

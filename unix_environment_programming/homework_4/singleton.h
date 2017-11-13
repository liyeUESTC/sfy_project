/*************************************************************************
	> File Name: singleton.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月13日 星期一 20时34分48秒
    > Function:单例模板类 供实现单例的类继承 
 ************************************************************************/

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "mutex.h"
#include "critical_area.h"

template<typename T>
class Singleton
{
public:
    static T *GetInstance();
    void DestoryInstance();
private:
    Singleton();
    virtual ~Singleton();
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
    static T *instance_;
    Mutex mutex_;
};

template<typename T>
static T * Singleton::GetInstance()
{
    if(nullptr == instance_)
    {
        CriticalArea critical_area(&mutex_);
        if(nullptr == instance_)  //双重检查  防止多线程同时访问时提高性能
        {
            instance_ = new T;
        }
    }
}

void Singleton::DestoryInstance()
{
    if(nullptr != instance_)
        delete instance_;
}
#endif

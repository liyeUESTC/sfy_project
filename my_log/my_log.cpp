/*************************************************************************
	> File Name: my_log.cpp
	> Author:shifangyan 
	> Mail: 852712053@qq.com
	> Created Time: 2017年09月16日 星期六 10时10分40秒
 ************************************************************************/
#include"my_log.h"

#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>

#include<iostream>




MyLog * MyLog::instance_ = nullptr;
std::string MyLog::log_buf_;

MyLog::MyLog()
{
    fd_ = open("my_log.txt",O_WRONLY|O_APPEND|O_CREAT,S_IRUSR|S_IRGRP|S_IROTH);
    if(-1 == fd_)
        std::cout << "log file open error\t" << errno << "\t" << strerror(errno) <<  std::endl;
    atexit(DestoryInstance);
}

MyLog* MyLog::GetInstance()
{
    if(nullptr == instance_)
    {
        instance_ = new MyLog();
    }
    return instance_;
}

void MyLog::DestoryInstance()
{
    UpdateBufToDisk();
    std::cout << "start destory" << std::endl;
    if(nullptr != instance_)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

std::string MyLog::GetLogMsg(char *ptr,int error_num)
{
    std::string str(ptr);
    str += "\terrno:" + std::to_string(error_num) + "\t" + strerror(error_num) + "\n";
    return str;
}
bool MyLog::WriteLogToBuf(char *ptr,int error_num)
{
    MyLog *my_log = GetInstance();
    if(nullptr == my_log)
    {
        std::cout << "log file ptr is null" << std::endl;
        return false;
    }
    if(nullptr == ptr)
    {
        std::cout << "log msg is null,please check" << std::endl;
        return false;
    }
    std::string log_msg = GetLogMsg(ptr,error_num);
    log_buf_ +=log_msg;

    if(log_buf_.size() > 100)
    {
        //std::cout << "start write disk" << std::endl;
        my_log->UpdateBufToDisk();
        log_buf_.clear();
      //  std::cout << log_buf_.size() << std::endl;
    }
    return true;
}

bool MyLog::UpdateBufToDisk()
{
    MyLog *my_log = GetInstance();
    if(nullptr == my_log)
    {
        std::cout << "log file ptr is null" << std::endl;
        return false;
    }
    int rec = write(my_log->fd(),log_buf_.c_str(),strlen(log_buf_.c_str()));
    if(rec != strlen(log_buf_.c_str()))
    {
        std::cout << "write log_buf to disk error" << std::endl;
        return false;
    }
    return true;
}

bool MyLog::WriteLogToDisk(char *ptr,int error_num)
{

    MyLog * my_log = MyLog::GetInstance();
    if(nullptr == my_log)
    {
        std::cout << "log ptr is null" << std::endl;
        return false;
    }
    if(nullptr == ptr)
    {
        std::cout << "log msg is null,please check" << std::endl;
        return false;
    }
    if(-1 == my_log->fd())
    {
        std::cout << "log file fd is -1,please check" << std::endl;
    }
    
    std::string log_msg = GetLogMsg(ptr,errno);
    int rec = write(my_log->fd(),log_msg.c_str(),strlen(log_msg.c_str()));
    if(rec != strlen(log_msg.c_str()))
    {
        std::cout << "write error" << std::endl;
        return false;
    }
    return true;
}


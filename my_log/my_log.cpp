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
//std::string MyLog::log_buf_;

MyLog::MyLog()
{
    fd_ = open("my_log.txt",O_WRONLY|O_APPEND|O_CREAT,S_IRUSR|S_IWUSR);
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
    MyLog *my_log = GetInstance();
    if(nullptr == my_log)
        return;
    my_log->UpdateBufToDisk();
    std::cout << "start destory" << std::endl;
    if(nullptr != instance_)
    {
        delete instance_;
        instance_ = nullptr;
    }
}

bool  MyLog::UpdateLogMsg(char *ptr,int error_num)
{
    MyLog *my_log = GetInstance();
    if(nullptr == my_log)
    {
        std::cout << "log file ptr is null" << std::endl;
        return false;
    }
    log_buf_  += "errno:" + std::to_string(error_num) + "      " + std::string(ptr) + "\n";
    if(log_buf_.size() > 100)
        my_log->UpdateBufToDisk();
    return true;
}

bool MyLog::WriteLog(char *ptr,int error_num)
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
    my_log->UpdateLogMsg(ptr,error_num);

    return true;
}

bool MyLog::UpdateBufToDisk()
{
    int rec = write(fd_,log_buf_.c_str(),strlen(log_buf_.c_str()));
    if(rec != strlen(log_buf_.c_str()))
    {
        std::cout << "write log_buf to disk error" << std::endl;
        return false;
    }
    log_buf_.clear();
    return true;
}

//bool MyLog::WriteLogToDisk(char *ptr,int error_num)
//{
//
//    MyLog * my_log = MyLog::GetInstance();
//    if(nullptr == my_log)
//    {
//        std::cout << "log ptr is null" << std::endl;
//        return false;
//    }
//    if(nullptr == ptr)
//    {
//        std::cout << "log msg is null,please check" << std::endl;
//        return false;
//    }
//    if(-1 == my_log->fd())
//    {
//        std::cout << "log file fd is -1,please check" << std::endl;
//    }
//    
//    std::string log_msg = GetLogMsg(ptr,errno);
//    int rec = write(my_log->fd(),log_msg.c_str(),strlen(log_msg.c_str()));
//    if(rec != strlen(log_msg.c_str()))
//    {
//        std::cout << "write error" << std::endl;
//        return false;
//    }
//    return true;
//}


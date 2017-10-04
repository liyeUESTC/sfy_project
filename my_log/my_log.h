/*************************************************************************
	> File Name: my_log.h
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 09时54分09秒
 ************************************************************************/

#ifndef MY_LOG_H_
#define MY_LOG_H_

#include <string>

class MyLog
{
private:
    MyLog();
    MyLog(const MyLog &my_log);
    MyLog & operator=(const MyLog &my_log);
    ~MyLog() {};
    static MyLog *instance_;
    std::string log_buf_;
    int fd_;
    static MyLog *GetInstance();
    static void DestoryInstance();
    bool UpdateBufToDisk();
    bool UpdateLogMsg(char *ptr,int error_num);
public:
    static bool WriteLog(char *ptr,int error_num);
//    static bool WriteLogToDisk(char *ptr,int error_num);
//    int fd() { return fd_;};
//    std::string log_buf() { return log_buf_;};
};
#endif

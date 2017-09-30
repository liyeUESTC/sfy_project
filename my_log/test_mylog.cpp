/*************************************************************************
	> File Name: test_mylog.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年09月16日 星期六 11时48分35秒
 ************************************************************************/

#include<iostream>
#include "my_log.h"
#include<fcntl.h>

using namespace std;

int main()
{
    int fd = open("111.txt",O_WRONLY|O_APPEND);
    char *log = "not find the file";
    int error_num = 4;
//    MyLog::WriteLogToDisk(log,errno);
//    for(int i = 0;i < 10000;++i)
    while(1)
        MyLog::WriteLogToBuf(log,errno);
    return 0;
}

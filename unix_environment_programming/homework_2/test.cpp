/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月05日 星期日 16时45分08秒
 ************************************************************************/

#include "file_operation.h"

#include <string.h>

#include <iostream>

int main(int argc,char *argv[])
{
    char buf[] = "0123456789";
    FileOperation file_operation("1.txt",O_RDWR|O_CREAT,S_IRWXU|S_IRWXG|S_IRWXO);
   // if(-1 == return_status.return_value())
   //     std::cout << strerror(return_status.return_errno()) << std::endl;
    ReturnStatus return_status = file_operation.Write(buf,10);
    if(-1 == return_status.return_value())
        std::cout << "1:" << strerror(return_status.return_errno()) << std::endl;
    char read_buf[20] ="";
   // ReturnStatus return_status = file_operation.MoveFilePtr(SEEK_SET,0);
   // if(-1 == return_status.return_value())
   //     std::cout << "2:" << strerror(return_status.return_errno()) << std::endl;
    return_status = file_operation.Read(read_buf,5);
   // read_buf[5] = '\0';
    if(-1 == return_status.return_value())
        std::cout << "3:" << strerror(return_status.return_errno()) << std::endl;
    std::cout << read_buf << std::endl;

}

/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年10月31日 星期二 16时28分02秒
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>


#include <iostream>

int main(int argc,char *argv[])
{
    //创建测试文件
//    int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);  //创建新文件
//    if(-1 == fd)    //出错返回
//    {
//        std::cout << "open new file error" << std::endl;
//        return -1;
//    }
//
//    char buf[100] = "0123456789";
//    int writen_size = write(fd,buf,strlen(buf));   //在测试文件中写入数据  供后续测试使用
//    if(-1 == writen_size)   //写入出错 则返回
//    {
//        std::cout << "write test file error" << std::endl;
//        return -1;
//    }
//
//    close(fd);

    //开始测试
    int fd = open(argv[1],O_RDWR|O_APPEND);   //打开测试文件并定位到文件尾
    if(-1 == fd)    //出错返回
    {
        std::cout << "open test file error" << std::endl;
        return -1;
    }

    int move_size = lseek(fd,0,SEEK_SET);   //将文件偏移量移到文件开头
    if(-1 == move_size)  //lseek出错  说明不能使用lseek移动文件指针
    {
        std::cout << "lseek error" << std::endl;
        return -1;
    }

    char buf[100] = "";
    int read_sum = 0;
    while(1)   //读文件直到文件尾
    {
        int read_size = read(fd,buf+read_sum,100);
        if(-1 == read_size)   //读文件出错返回
        {
            std::cout << "read error" << std::endl;
            return -1;
        }
        else if(0 == read_size)  //读到文件尾  返回
            break;
        read_sum += read_size;  //修改已读到的数据量
    }

    std::cout << buf << std::endl;   //输出文件内容 
}

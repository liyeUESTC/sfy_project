/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017��10��31�� ���ڶ� 16ʱ28��02��
 ************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>


#include <iostream>

int main(int argc,char *argv[])
{
    //���������ļ�
//    int fd = open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);  //�������ļ�
//    if(-1 == fd)    //������
//    {
//        std::cout << "open new file error" << std::endl;
//        return -1;
//    }
//
//    char buf[100] = "0123456789";
//    int writen_size = write(fd,buf,strlen(buf));   //�ڲ����ļ���д������  ����������ʹ��
//    if(-1 == writen_size)   //д����� �򷵻�
//    {
//        std::cout << "write test file error" << std::endl;
//        return -1;
//    }
//
//    close(fd);

    //��ʼ����
    int fd = open(argv[1],O_RDWR|O_APPEND);   //�򿪲����ļ�����λ���ļ�β
    if(-1 == fd)    //������
    {
        std::cout << "open test file error" << std::endl;
        return -1;
    }

    int move_size = lseek(fd,0,SEEK_SET);   //���ļ�ƫ�����Ƶ��ļ���ͷ
    if(-1 == move_size)  //lseek����  ˵������ʹ��lseek�ƶ��ļ�ָ��
    {
        std::cout << "lseek error" << std::endl;
        return -1;
    }

    char buf[100] = "";
    int read_sum = 0;
    while(1)   //���ļ�ֱ���ļ�β
    {
        int read_size = read(fd,buf+read_sum,100);
        if(-1 == read_size)   //���ļ�������
        {
            std::cout << "read error" << std::endl;
            return -1;
        }
        else if(0 == read_size)  //�����ļ�β  ����
            break;
        read_sum += read_size;  //�޸��Ѷ�����������
    }

    std::cout << buf << std::endl;   //����ļ����� 
}

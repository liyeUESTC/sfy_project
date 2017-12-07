/*************************************************************************
	> File Name: file_operation.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017��11��05�� ������ 15ʱ59��51��
 ************************************************************************/

#include "file_operation.h"

#include <errno.h>

#include <string.h>

#include <iostream>
#include <string>

#include "return_status.h"

const int kWriteCacheSize = 4096;
const int kReadCacheSize = 4096;

FileOperation::FileOperation(const char *file_name,int flags,mode_t mode)
{
    fd_ = -1;
    //�����O_CREAT ��Ҫ����������
    if(flags & O_CREAT)
    {
        if(0 == mode)
        {
            std::cout << "��Ҫ���������������ļ�" << std::endl;
            throw "��Ҫ��������";
        }
        fd_ = open(file_name,flags,mode);
        if( -1 == fd_)
            throw ReturnStatus(-1,errno);
    }
    else
    {
        fd_ = open(file_name,flags);
        if(-1 == fd_)
            throw ReturnStatus(-1,errno);
    }

    //������д���� ������
    write_cache_ = new char[kWriteCacheSize];
    read_cache_ = new char[kReadCacheSize];
    write_cache_size_ = 0;
    read_cache_size_ = 0;
}

FileOperation::~FileOperation()
{
    //����ļ���������Ч ������������д����� ���ر��ļ�
    if(fd_ != -1)
    {
        FlushWrite();
        close(fd_);
    }
    //���ļ����д��������
    delete [] write_cache_;
    delete [] read_cache_;
}

ReturnStatus FileOperation::MoveFilePtr(off_t offset,int whence)
{
    //����ϵͳ���� �ƶ��ļ�ָ��
    int rec = lseek(fd_,offset,whence);
    return ReturnStatus(rec,errno);
}



ReturnStatus FileOperation::Write(const void *buf_ptr,int write_size,off_t offset,
    int whence)
{
    //�ƶ��ļ�ָ�뵽ָ��λ��  Ĭ��λ��Ϊ�ļ�β
    ReturnStatus return_status = MoveFilePtr(offset,whence);
    if(-1 == return_status.return_value())
        return return_status;
    //����ļ������໺�治��  �Ȱѻ���д�����
    if(write_cache_size_+ write_size > kWriteCacheSize)
    {
        ReturnStatus return_status = FlushWrite();
        if(-1 == return_status.return_value())
            return return_status;     
    }

    int i = 0;
    //���д�����ݱ��ļ����������  �����ο��������� ��д����� ֱ��ʣ��д������С���ļ������໺��
    while( (write_size > kWriteCacheSize) )
    {
        memcpy(write_cache_,buf_ptr+i*kWriteCacheSize,kWriteCacheSize);
        write_cache_size_ = kWriteCacheSize;
        ReturnStatus return_status = FlushWrite();
        if(-1 == return_status.return_value())
            return return_status;
        write_size -= kWriteCacheSize;
        ++i;
    }

    //��ʣ�����ݿ���������
    memcpy(write_cache_,buf_ptr+i*kWriteCacheSize,write_size);
    write_cache_size_ += write_size;
    return ReturnStatus(0,0);
}

ReturnStatus FileOperation::Read(void *buf_ptr,int read_size,off_t offset,
    int whence)
{
    //temp_size��¼�Ѿ������û�������ֽ���
    int temp_size = read_cache_size_;
    //���Ҫ������ֽڴ����໺��ʣ���ֽ� ��ȥ������
    if(read_size > read_cache_size_)
    {
        //���໺��ʣ���ֽڿ������û�����
        memcpy(buf_ptr,read_cache_+kReadCacheSize-read_cache_size_,read_cache_size_);
        read_size -= read_cache_size_;
        read_cache_size_ = 0;
        //����д�뻺��д�뵽���� ��֤��дһ��
        ReturnStatus return_status = FlushWrite();
        if(-1 == return_status.return_value() )
            return return_status;
        //�ƶ��ļ�ָ��
        return_status = MoveFilePtr(offset,whence);
        if(-1 == return_status.return_value())
            return return_status;
        //����û�Ҫ������ֽڴ����໺�泤�� �ֶ����ζ����໺�� ���������û�����
        while( (read_size > kReadCacheSize) )
        {
            return_status = FlushRead();
            if(-1 == return_status.return_value())
                return return_status;
            memcpy(buf_ptr+temp_size,read_cache_,kReadCacheSize);
            temp_size += kReadCacheSize;
            read_size -= kReadCacheSize;
        }

    }
    //��ʣ���ֽڿ������û�����
    ReturnStatus return_status = FlushRead();
    if(-1 == return_status.return_value())
        return return_status;
    memcpy(buf_ptr+temp_size,read_cache_,read_size);
    read_cache_size_ -= (read_size-temp_size);
    return ReturnStatus(0,0);
}

ReturnStatus FileOperation::FlushWrite()
{
    if(0 == write_cache_size_)
        return ReturnStatus(0,0);
    int writed_size = 0;  //�Ѿ�д���С
    //ѭ��д�����  ֱ������д�뻺��д��
    while(1)
    {
        int size = write(fd_,write_cache_+writed_size,write_cache_size_- writed_size);
        if(-1 == size)
            return ReturnStatus(-1,errno);
        else
        {
            writed_size += size;
            if( writed_size == write_cache_size_)
            {
                write_cache_size_ = 0;
                return ReturnStatus(0,0);
            }
        }
    }
}

ReturnStatus FileOperation::FlushRead()
{
    if(kReadCacheSize == read_cache_size_)
        return ReturnStatus(0,0);
//    std::cout << "go to there" << std::endl;
    //    ѭ���Ӵ��̶� ֱ�������໺�������ļ�β
    while(1)
    {
//        std::cout << "read_cache_size_" << read_cache_size_ << std::endl;
        int size = read(fd_,read_cache_+read_cache_size_,kReadCacheSize-read_cache_size_);
        if(-1 == size)
            return ReturnStatus(-1,errno);
        //�����ļ�β
        else if(0 == size)
        {
            //std::cout << "go to there 1" << std::endl; 
            return ReturnStatus(0,0);
        }
        else
        {
//            std::cout << "size:" << size << std::endl;
            read_cache_size_ += size;
            if(read_cache_size_ == kReadCacheSize)
                return ReturnStatus(0,0);
        }
    }
}







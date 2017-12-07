/*************************************************************************
	> File Name: file_operation.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月05日 星期日 15时59分51秒
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
    //如果有O_CREAT 需要传三个参数
    if(flags & O_CREAT)
    {
        if(0 == mode)
        {
            std::cout << "需要三个参数来创建文件" << std::endl;
            throw "需要三个参数";
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

    //申请类写缓存 读缓存
    write_cache_ = new char[kWriteCacheSize];
    read_cache_ = new char[kReadCacheSize];
    write_cache_size_ = 0;
    read_cache_size_ = 0;
}

FileOperation::~FileOperation()
{
    //如果文件描述符有效 将缓存内数据写入磁盘 并关闭文件
    if(fd_ != -1)
    {
        FlushWrite();
        close(fd_);
    }
    //将文件类读写缓存销毁
    delete [] write_cache_;
    delete [] read_cache_;
}

ReturnStatus FileOperation::MoveFilePtr(off_t offset,int whence)
{
    //调用系统函数 移动文件指针
    int rec = lseek(fd_,offset,whence);
    return ReturnStatus(rec,errno);
}



ReturnStatus FileOperation::Write(const void *buf_ptr,int write_size,off_t offset,
    int whence)
{
    //移动文件指针到指定位置  默认位置为文件尾
    ReturnStatus return_status = MoveFilePtr(offset,whence);
    if(-1 == return_status.return_value())
        return return_status;
    //如果文件操作类缓存不够  先把缓存写入磁盘
    if(write_cache_size_+ write_size > kWriteCacheSize)
    {
        ReturnStatus return_status = FlushWrite();
        if(-1 == return_status.return_value())
            return return_status;     
    }

    int i = 0;
    //如果写入数据比文件操作缓存大  分批次拷贝到缓存 并写入磁盘 直到剩余写入数据小于文件操作类缓存
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

    //将剩余数据拷贝到缓存
    memcpy(write_cache_,buf_ptr+i*kWriteCacheSize,write_size);
    write_cache_size_ += write_size;
    return ReturnStatus(0,0);
}

ReturnStatus FileOperation::Read(void *buf_ptr,int read_size,off_t offset,
    int whence)
{
    //temp_size记录已经读到用户缓存的字节数
    int temp_size = read_cache_size_;
    //如果要求读的字节大于类缓存剩余字节 就去读磁盘
    if(read_size > read_cache_size_)
    {
        //将类缓存剩余字节拷贝到用户缓存
        memcpy(buf_ptr,read_cache_+kReadCacheSize-read_cache_size_,read_cache_size_);
        read_size -= read_cache_size_;
        read_cache_size_ = 0;
        //将类写入缓存写入到磁盘 保证读写一致
        ReturnStatus return_status = FlushWrite();
        if(-1 == return_status.return_value() )
            return return_status;
        //移动文件指针
        return_status = MoveFilePtr(offset,whence);
        if(-1 == return_status.return_value())
            return return_status;
        //如果用户要求读的字节大于类缓存长度 分多批次读入类缓存 并拷贝到用户缓存
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
    //将剩余字节拷贝到用户缓存
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
    int writed_size = 0;  //已经写入大小
    //循环写入磁盘  直到将类写入缓存写完
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
    //    循环从磁盘读 直到读满类缓存或读到文件尾
    while(1)
    {
//        std::cout << "read_cache_size_" << read_cache_size_ << std::endl;
        int size = read(fd_,read_cache_+read_cache_size_,kReadCacheSize-read_cache_size_);
        if(-1 == size)
            return ReturnStatus(-1,errno);
        //读到文件尾
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







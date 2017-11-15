/*************************************************************************
	> File Name: file_operation.h
	> Author: 
	> Mail: 
	> Created Time: 2017��11��05�� ������ 15ʱ34��49��
 ************************************************************************/

#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "return_status.h"

class FileOperation
{
public:
    FileOperation(const char *file_name,int flags,mode_t mode = 0);
    ~FileOperation();
    ReturnStatus MoveFilePtr(off_t offset,int whence);
    ReturnStatus Write(const char *buf_ptr,int write_size,off_t offset =0,
        int whence = SEEK_END);
    ReturnStatus Read(char *buf_ptr,int read_size,off_t offset = 0,
        int whence = SEEK_SET);

    //��ֹ����
    FileOperation(const FileOperation &) = delete;
    FileOperation &operator= (const FileOperation &) = delete;
private:
    int fd_;
    char *write_cache_;
    char *read_cache_;
    int write_cache_size_;  //д�����Ѵ����ݴ�С
    int read_cache_size_;   //�������Ѵ����ݴ�С
    ReturnStatus FlushWrite();
    ReturnStatus FlushRead();
};
#endif

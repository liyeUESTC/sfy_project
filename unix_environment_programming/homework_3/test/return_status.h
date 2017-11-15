/*************************************************************************
	> File Name: ReturnStatus.h
	> Author: 
	> Mail: 
	> Created Time: 2017年11月05日 星期日 15时11分24秒
 ************************************************************************/

#ifndef RETURNSTATUS_H
#define RETURNSTATUS_H


class ReturnStatus
{
public:
    ReturnStatus(int return_value,int errno_value);
    int return_value();
    int return_errno();
private:
    int return_value_;
    int return_errno_;
};
#endif

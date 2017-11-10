/*************************************************************************
	> File Name: return_status.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年11月05日 星期日 15时20分55秒
 ************************************************************************/

#include "return_status.h"

ReturnStatus::ReturnStatus(int return_value,int errno_value)
{
    return_value_ = return_value;
    return_errno_ = errno_value;
}

int ReturnStatus::return_value()
{
    return return_value_;
}

int ReturnStatus::return_errno()
{
    return return_errno_;
}

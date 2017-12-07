/*************************************************************************
	> File Name: ReturnStatus.h
	> Author: 
	> Mail: 
	> Created Time: 2017��11��05�� ������ 15ʱ11��24��
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

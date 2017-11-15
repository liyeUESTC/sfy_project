/*************************************************************************
	> File Name: task.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月13日 星期一 22时00分04秒
    > Function: 
 ************************************************************************/

#include "task.h"

Task::Task()
{
    task_ID_ = 0;
    //result_ = nullptr;
}

Task::~Task()
{

}

int Task::task_ID()
{
    return task_ID_;
}

void Task::SetID(int task_ID)
{
    task_ID_ = task_ID;
}

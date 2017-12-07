/*************************************************************************
	> File Name: task_managerment.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月13日 星期一 21时24分37秒
    > Function: 
 ************************************************************************/
#include "task_managerment.h"

#include <iostream>


TaskManagerment::TaskManagerment()
{
    task_id_max_ = 0;
}

int TaskManagerment::CreateTaskID()
{
    return  ++task_id_max_;
}

bool TaskManagerment::DestoryTask(int task_ID)
{
    for(auto iter = task_map_.begin();iter != task_map_.end();++iter)
    {
        if(task_ID == iter->first && nullptr != iter->second)
        {
            delete iter->second;
            iter->second = nullptr;
            A
            return true;
        }
    }
    return false;
}

void TaskManagerment::DestoryAllTask()
{
    for(auto iter = task_map_.begin();iter != task_map_.end();++iter)
    {
        if(iter->second != nullptr)
            delete iter->second;
    }
    task_map_.clear();
}

TaskManagerment::~TaskManagerment()
{
    std::cout << "destory TaskManagerment" << std::endl;
    DestoryAllTask();
}

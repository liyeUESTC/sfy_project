/*************************************************************************
	> File Name: task_managerment.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月13日 星期一 21时24分37秒
    > Function: 
 ************************************************************************/

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
    for(auto iter = task_vec_.begin();iter != task_vec_.end();++iter)
    {
        if(task_ID == (*iter)->task_ID())
        {
            delete *iter;
            *iter = nullptr;
            return true;
        }
    }
    return false;
}

void TaskManagerment::DestoryAllTask()
{
    for(auto iter = task_vec_.begin();iter != task_vec_.end();++iter)
    {
        if(*iter != nullptr)
        {
            delete *iter;
    }
    task_vec_.clear();
}

/*************************************************************************
	> File Name: task_managerment.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月12日 星期日 16时48分04秒
    > Function:线程任务管理类 负责创建任务和销毁任务 
 ************************************************************************/

#ifndef TASK_MANAGERMENT_H_
#define TASK_MANAGERMENT_H_

#include <map>

#include "task.h"
#include "singleton.h"

class TaskManagerment:public Singleton<TaskManagerment>
{
public:
    friend class Singleton;
    int CreateTaskID();
    Task *GetTask(int task_ID);
    template<typename T>
    Task *CreatTask();
    bool DestoryTask(int task_ID);
    void DestoryAllTask();
private:
    TaskManagerment();
    TaskManagerment(const TaskManagerment &) = delete;
    TaskManagerment &operator=(const TaskManagerment &) = delete;
    std::map<int,Task *> task_map_;
    int task_id_max_;
};

template<typename T>
Task *TaskManagerment::CreatTask()
{
    T *task_ptr = new T;
    int task_ID = CreateTaskID();
    task_ptr->SetID(task_ID);
    task_map_.insert(std::pair<int,Task *>(task_ID,task_ptr));
    return task_ptr;
}
#endif

/*************************************************************************
	> File Name: thread_task.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月12日 星期日 16时11分19秒
    > Function:线程执行任务的基类 自己要执行的类继承这个基类 
 ************************************************************************/

#ifndef TASK_H_
#define TASK_H_

//#include "task_managerment.h"

class Task
{
public:
    friend class TaskManagerment;
    virtual void TaskFunction() = 0;
    virtual void PrintResult() = 0;
//    virtual void *GetResult() = 0;
    Task();
    virtual ~Task();
    int task_ID();
protected:
    int task_ID_;
private:
    void SetID(int task_ID);
};
#endif

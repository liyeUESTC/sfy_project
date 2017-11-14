/*************************************************************************
	> File Name: test.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月14日 星期二 21时27分38秒
    > Function: 
 ************************************************************************/

#include <iostream>

#include "task.h"
#include "task_managerment.h"
#include "thread_pool_managerment.h"

class AddTask:public Task
{
public:
    AddTask();
    void SetAddNum(int num1,int num2);
    void TaskFunction();
    void PrintResult();
private:
    int add_num1_;
    int add_num2_;
    int result_;
};

AddTask::AddTask()
{
    add_num1_=0;
    add_num2_=0;
    result_=0;
}

void AddTask::SetAddNum(int num1,int num2)
{
    add_num1_ = num1;
    add_num2_ = num2;
}

void AddTask::TaskFunction()
{
    result_ = add_num1_+add_num2_;
}

void PrintResult()
{
    std::cout << "task ID:" << task_ID_ 
              << "  result:" << result_ 
              << std::endl;
}

int main(int argc,char *argv[])
{
    ThreadPoolManagerment::GetInstance()->Run();
    Task *task = TaskManagerment::GetInstance()->CreateTask<AddTask>();
    task->SetAddNum(5,6);
    ThreadPoolManagerment::GetInstance()->PostTask(task);
    Task *task = ThreadPoolManagerment::GetInstance()->GetTask();
    task->PrintResult();

    ThreadPoolManagerment::GetInstance()->StopAllThread();
    ThreadPoolManagerment::GetInstance()->Destory();
    TaskManagerment::GetInstance()->DestoryAllTask();
    TaskManagerment::GetInstance()->Destory();
    return 0;
}

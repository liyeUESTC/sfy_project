/*************************************************************************
	> File Name: thread_pool_managerment.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月14日 星期二 20时54分09秒
    > Function: 
 ************************************************************************/

#include "thread_pool_managerment.h"

ThreadPoolManagerment::ThreadPoolManagerment(int thread_num)
{
    thread_num_ = thread_num;
    allocate_thread_num_ = 0;
}

ReturnStatus ThreadPoolManagerment::Run()
{
    for(int i = 0;i < thread_num_;++i)
    {
        Thread *thread = new Thread;
        ReturnStatus return_status = thread->Run();
        if(-1 == return_status.return_value())
        {
            std::cout << "thread Run error" << std::endl;
            return ReturnStatus(-1,0);
        }
        thread_vec_.push_back(thread);
    }
}

ReturnStatus ThreadPoolManagerment::PostTask(Task *task)
{
    allocate_thread_num_++;
    if(allocate_thread_num_ > thread_num_)
        allocate_thread_num_ = 1;
    thread_vec_[allocate_thread_num_-1]->ReceiveTask(task);
    return ReturnStatus(0,0);
}

ReturnStatus ThreadPoolManagerment::RecycleTask(Task *task)
{
    completed_task_queue_.PostMessage(task);
    return ReturnStatus(0,0);
}

Task *ThreadPoolManagerment::GetTask()
{
    Task *task;
    completed_task_queue_.PostMessage.GetMessage(task,true);
    return task;
}

void ThreadPoolManagerment::StopAllThread()
{
    for(auto iter = thread_vec_.begin();iter != thread_vec_.end();++iter)
    {
        (*iter)->Stop();       
    }
    sleep(1);
    for(auto iter = thread_vec_.begin();iter != thread_vec_.end();++iter)
    {
        delete *iter;       
    }
    thread_vec_.clear();
}




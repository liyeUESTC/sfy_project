/*************************************************************************
	> File Name: thread_pool_managerment.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月14日 星期二 20时30分18秒
    > Function: 
 ************************************************************************/

#ifndef THREAD_POOL_MANAGERMENT_H_
#define THREAD_POOL_MANAGERMENT_H_

#include <vector>

#include "task.h"
#include "thread.h"
#include "singleton.h"
#include "thread_message_queue.h"

class ThreadPoolManagerment:public Singleton<ThreadPoolManagerment>
{
public:
    friend Singleton<ThreadPoolManagerment>;
    ReturnStatus Run();
    ReturnStatus PostTask(Task *task);
//    ReturnStatus AllocateTask(Task *task);
    ReturnStatus RecycleTask(Task *task);
    Task *GetTask();
    void StopAllThread();
private:
    ThreadPoolManagerment(int thread_num);
    ThreadPoolManagerment(const ThreadPoolManagerment &) = delete;
    ThreadPoolManagerment &operator=(const ThreadPoolManagerment &) = delete;
    std::vector<Thread *>thread_vec_;
    int thread_num_;
    int allocate_thread_num_;
    ThreadMessageQueue<Task> completed_task_queue_;
};
#endif

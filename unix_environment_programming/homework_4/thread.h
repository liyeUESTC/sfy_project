/*************************************************************************
	> File Name: thread.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月14日 星期二 19时33分45秒
    > Function:线程封装类  主要为线程池的线程类 负责接收线程池控制类下发的任务类 并执行 返回任务类
 ************************************************************************/

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

#include "thread_message_queue.h"
#include "task.h"

class Thread
{
public:
    Thread();
    //~Thread();
    ReturnStatus Run();
    void ReceiveTask(Task *task);
    void Stop();
    Thread(const Thread &) = delete;
    Thread &operator=(const Thread &) = delete;
private:
    static void *StartFunctionOfThread(void *p);
    ThreadMessageQueue<Task> message_;
    pthread_t thread_ID_;
    bool is_exit_;
    bool is_detach_;
};
#endif

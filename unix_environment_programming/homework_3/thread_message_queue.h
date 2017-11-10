/*************************************************************************
	> File Name: thread_message_queue.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月10日 星期五 09时53分40秒
 ************************************************************************/

#ifndef THREAD_MESSAGE_QUEUE_H_
#define THREAD_MESSAGE_QUEUE_H_

#include "my_queue.h"

#include <unistd.h>

#include "critical_area.h"

template<typename T>
class ThreadMessageQueue
{
public:
    ReturnStatus PostMessage(const T &message);
    ReturnStatus GetMessage(T &message,bool is_wait);
private:
    MyQueue<T> message_queue_;
};


ReturnStatus ThreadMessageQueue::PostMessage(const T &message)
{
    CriticalArea critical_area;
    message_queue_.Push(message);
}

ReturnStatus GetMessage(T &message,bool is_wait)
{
    while(1)
    {
        {
            CriticalArea critical_area;
            if(message_queue_.Empty() && !is_wait)
                return ReturnStatus(-1,0);
            else if(!message_queue_.Empty())
            {
                message = message_queue_.Front();
                message_queue_.Pop();
                break;
            }
        }
        usleep(100000);
    }   
}
#endif
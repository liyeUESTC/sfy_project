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
#include "mutex.h"

template<typename T>
class ThreadMessageQueue
{
public:
    ReturnStatus PostMessage(T *message);
    ReturnStatus GetMessage(T *&message,bool is_wait);
private:
    MyQueue<T *> message_queue_;
    Mutex mutex_;
};

//发送消息函数
template<typename T>
ReturnStatus ThreadMessageQueue<T>::PostMessage(T *message) 
{
    CriticalArea critical_area(&mutex_); //临界区
    message_queue_.Push(message);  //在队尾添加
}

//取消息函数 
template<typename T>
ReturnStatus ThreadMessageQueue<T>::GetMessage(T *&message,bool is_wait)
{
    while(1)
    {
        {
            CriticalArea critical_area(&mutex_); //临界区
            if(message_queue_.Empty() && !is_wait)  //如果不等待 且消息队列为空 直接返回
                return ReturnStatus(-1,0);
            else if(!message_queue_.Empty())  //如果消息队列不为空  取消息
            {
                message = message_queue_.Front(); //取队首
                message_queue_.Pop();  //删除队首
                return ReturnStatus(0,0);
            }
        }
        usleep(100000);
    }   
}
#endif

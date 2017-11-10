/*************************************************************************
	> File Name: my_queue.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年11月09日 星期四 21时45分04秒
 ************************************************************************/

#ifndef MY_QUEUE_H_
#define MY_QUEUE_H_

#include "linked_list.h"

template<typename T>
class MyQuenue
{
public:
    bool Empty();
    int Size();
    T &Front();
    T &Back();
    void Pop();
    void Push(const T &element);
private:
    LinkedList<T> linked_list_;    
}

bool MyQuenue<T>::Empty()
{
    return linked_list_.Empty();
}

int MyQuenue<T>::Size()
{
    return linked_list_.Size();
}

T &MyQuenue<T>::Front()
{
    return linked_list_.Get(0);
}

T &MyQuenue<T>::Back()
{
    return linked_list_.Get(linked_list_.Size()-1);
}

void MyQuenue<T>::Pop()
{
    linked_list_.Erase(0);
}

void MyQuenue<T>::Push(const T &element)
{
    linked_list_.PushBack(element);
}
#endif

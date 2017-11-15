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
class MyQueue
{
public:
    bool Empty();
    int Size();
    T Front();
    T Back();
    void Pop();
    void Push(const T &element);
private:
    LinkedList<T> linked_list_;    
};

template<typename T>
bool MyQueue<T>::Empty()
{
    return linked_list_.Empty();
}

template<typename T>
int MyQueue<T>::Size()
{
    return linked_list_.Size();
}

template<typename T>
T MyQueue<T>::Front()
{
    return linked_list_.Get(0);
}

template<typename T>
T MyQueue<T>::Back()
{
    return linked_list_.Get(linked_list_.Size()-1);
}

template<typename T>
void MyQueue<T>::Pop()
{
    linked_list_.Erase(0);
}

template<typename T>
void MyQueue<T>::Push(const T &element)
{
    linked_list_.PushBack(element);
}
#endif

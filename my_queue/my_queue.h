#include <iostream>
#include <memory>
#include <stdexcept>

//采用环形数组存储数据 front_position指向队列首位元素的下一位
//back_position指向队尾元素 
//front_position = back_position 队列为空
//队列最多只能存储max_size-1个元素 避免元素满时 front_position = back_position
template <typename T>
class MyQueue
{
public:
    MyQueue(int size = 5);
    bool empty() const;
    int size() const;
    T front() const;
    T back() const;
    bool pop();
    void push(const T data);
private:
    int front_position_;
    int back_position_;
    int max_size_;
    std::shared_ptr<T> ptr_;  
    std::shared_ptr<T>  ChangeSize(const std::shared_ptr<T> ptr,int src_size,int dst_size);
};
template <typename T>
MyQueue<T>::MyQueue(int size):front_position_(0),back_position_(0),max_size_(5)
{
    ptr_ = std::shared_ptr<T>(new T[max_size_],[](T *p){delete [] p;});
}

template <typename T>
bool MyQueue<T>::empty() const
{
    return (front_position_ == back_position_);
}

template <typename T>
int MyQueue<T>::size() const
{
    if(front_position_ > back_position_)
        return back_position_+max_size_ - front_position_;
    return back_position_-front_position_;
}

template <typename T>
T MyQueue<T>::front() const  
{
    if(front_position_ == back_position_)
        throw std::range_error("队列为空 违规操作");
    int temp_position = (front_position_ +1) % max_size_;
    return *(ptr_.get()+temp_position); 
}

template <typename T>
T MyQueue<T>::back() const
{
    if(front_position_ == back_position_)
        throw std::range_error("队列为空 违规操作");
    return *(ptr_.get()+back_position_);
}

template <typename T>
bool MyQueue<T>::pop()
{
    if(front_position_ == back_position_)
        return false;
    front_position_ =  (front_position_ +1) % max_size_;
    return true;
}

template <typename T>
std::shared_ptr<T> MyQueue<T>::ChangeSize(const std::shared_ptr<T> ptr,int src_size,int dst_size)
{
    if(dst_size <= src_size)
        throw std::range_error("申请数组小于等于原数组");
    std::shared_ptr<T> temp_ptr(new T[dst_size],[](T *p){delete p;});
    int start = (front_position_+1) % max_size_;
    if(start > back_position_) //成环
    {
        std::copy(ptr.get()+start,ptr.get()+src_size,temp_ptr.get());
        std::copy(ptr.get(),ptr.get()+back_position_+1,temp_ptr.get()+src_size-start);
    }
    else
        std::copy(ptr.get()+start,ptr.get()+start+max_size_-1,temp_ptr.get());
    return temp_ptr;
}

template <typename T>
void MyQueue<T>::push(T data)
{
    if( (back_position_ +1) % max_size_ == front_position_) //空间不够
    {
        ptr_ = ChangeSize(ptr_,max_size_,2*max_size_);
        front_position_ = 2*max_size_ - 1;
        back_position_ = max_size_ - 2;
        max_size_ = 2*max_size_;
    }
    back_position_ = (back_position_ +1) % max_size_;
    *(ptr_.get()+back_position_) = data; 
}


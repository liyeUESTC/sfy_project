#include <memory>
#include <exception>
#include <iostream>

template <typename T>
class MyStack
{
public:
    MyStack();
    MyStack(int size);
    bool empty();
    int size();
    T top();
    bool pop();
    void push(const T data);
private:
    int size_;
    int max_size_;
    std::shared_ptr<T>  ptr_;
    std::shared_ptr<T> ChangeSize(std::shared_ptr<T> ptr,int src_size,int dst_size);
};

template <typename T>
MyStack<T>::MyStack()
{
    size_ = 0;
    max_size_ = 5;
    ptr_ = std::shared_ptr<T>(new T[max_size_],[]( T *p){ delete [] p;});
}

template <typename T>
MyStack<T>::MyStack(int size)
{
    size_ = 0;
    max_size_ = size;
    ptr_ = std::shared_ptr<T>(new T[max_size_],[](T *p) {delete [] p;});
}

template <typename T>
bool MyStack<T>::empty()
{
    if(size_ == 0)
        return true;
    return false;
}

template <typename T>
int MyStack<T>::size()
{
    return size_;
}

template <typename T>
T MyStack<T>::top()
{
    if(size_ == 0)
        throw std::range_error("对空栈进行非法操作");
    return *(ptr_.get()+size_-1);
}

template <typename T>
bool MyStack<T>::pop()
{
    if(size_ < 1)
        throw std::range_error("对空栈进行非法操作");
    size_--;
    return true;
}

template <typename T>
void MyStack<T>::push(const T data)
{
    *(ptr_.get()+size_) = data;
    size_++;
    if(size_ >= max_size_)
    {
        ptr_ = ChangeSize(ptr_,max_size_,2*max_size_);
        max_size_ *= 2;
    }
}

template <typename T>
std::shared_ptr<T> MyStack<T>::ChangeSize(std::shared_ptr<T> ptr,int src_size,int dst_size)
{
    std::shared_ptr<T> temp_ptr(new T[dst_size],[](T *p) { delete [] p;});
    if(src_size > dst_size)
        src_size = dst_size;
    std::copy(ptr.get(),ptr.get()+src_size,temp_ptr.get());
    return temp_ptr;
}



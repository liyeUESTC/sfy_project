/*************************************************************************
	> File Name: my_dictionary.h
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2017 02:35:31 PM CST
 ************************************************************************/

#ifndef _MY_DICTIONARY_H
#define _MY_DICTIONARY_H

#include <vector>

template<typename T,typename U>
class MyPair
{
public:
    MyPair(T arg1,U arg2):first_(arg1),second_(arg2)
    {}
    MyPair(const MyPair &my_pair)
    {
        first_ = my_pair.first_;
        second_ = my_pair.second_;
    }
    MyPair & operator=(const MyPair &my_pair)
    {
        first_ = my_pair.first_;
        second_ = my_pair.second_;
        return *this;
    }
    T first_;
    U second_;
};

template<typename W,typename X>
class MyDictionary
{
private:
    std::vector<MyPair<W,X> > dictionary_;
public:
    void Insert(const MyPair<W,X> &my_pair);
    bool Erase(const W &w);
    MyPair<W,X> * Find(const W &w) const;
    bool Empty() const;
    int Size() const;
};

template<typename W,typename X>
void MyDictionary<W,X>::Insert(const MyPair<W,X> &my_pair)
{
    dictionary_.push_back(my_pair);
}

template<typename W,typename X>
MyPair<W,X> *  MyDictionary<W,X>::Find(const W &w) const
{
    for(int i = 0;i < dictionary_.size();++i)
        {
            if(w == dictionary_[i].first_)
            {
                MyPair<W,X> *ptr = const_cast<MyPair<W,X> *> (&dictionary_[i]);
                return ptr;
            }
        }
        return nullptr;
}

template<typename W,typename X>
bool MyDictionary<W,X>::Erase(const W &w)
{
    auto iter = dictionary_.begin();
    for (;iter != dictionary_.end();++iter)
    {
        if(w == iter->first_)
            break;
    }
    if(dictionary_.end() == iter)
        return false;
    dictionary_.erase(iter);
    return true;
}

template<typename W,typename X>
bool MyDictionary<W,X>::Empty() const
{
    if(dictionary_.empty())
        return true;
    return false;
}

template<typename W,typename X>
int MyDictionary<W,X>::Size() const
{
    return dictionary_.size();
}


#endif

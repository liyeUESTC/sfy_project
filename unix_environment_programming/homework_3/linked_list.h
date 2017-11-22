#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>

template <typename T>
struct LinkedListNode
{
	T data;
	LinkedListNode<T> *next_node;

	LinkedListNode():next_node(nullptr) {}
	LinkedListNode(const T& data_param) :data(data_param),next_node(nullptr) {}
	LinkedListNode(const T& data_param, LinkedListNode<T>  *next_node_param) :data(data_param),next_node(next_node_param) {}
};

template <typename T>
class LinkedList
{
public:
	LinkedList() :header_node_(nullptr), end_node_(nullptr), list_size_(0) {};
	LinkedList(int list_size, const T& t);
	~LinkedList();
	bool Empty() const { return header_node_ == nullptr; }
	int Size() const { return list_size_; }
	void SetSize(int size);
	T Get(int index) const;
	void Set(int index,const T& t);
	int Index(const T& t) const;
	void Erase(int index);
	void Insert(int index, const T& t);
	void PushBack(const T& t);
//	void RemoveRange(int from_index, int to_index);
private:
	LinkedListNode<T> *header_node_;
	LinkedListNode<T> *end_node_;
	int list_size_;
};

//链表构造函数 可指定大小和元素内容
template <typename T>
LinkedList<T>::LinkedList(int list_size,const T&t)
{
	list_size_ = list_size;
	LinkedListNode<T> *temp_node;
	for (int i = 0; i < list_size_; ++i)
	{
		LinkedListNode<T>* linked_list_node = new LinkedListNode<T>(t);
		if (0 == i)
			header_node_ = linked_list_node;
		else
			temp_node->next_node = linked_list_node;
		temp_node = linked_list_node;
	}

	temp_node->next_node = nullptr;
	end_node_ = temp_node;
}

//链表析构函数 删除所有动态申请的内存
template <typename T>
LinkedList<T>::~LinkedList()
{
	while (header_node_ != nullptr)
	{
		LinkedListNode<T> * next_node = header_node_->next_node;
		delete header_node_;
		header_node_ = next_node;
	}
}

//返回给定序号的元素  范围：0到list_size_-1
template <typename T>
T LinkedList<T>::Get(int index) const
{
    if(0 == index) 
    {
        return header_node_->data;
    }
    else if(list_size_-1 == index)
        return end_node_->data;
	LinkedListNode<T> *linked_list_node = header_node_;
	for (int i = 0; i <= index; ++i)
	{
		linked_list_node = linked_list_node->next_node;
	}
	return linked_list_node->data;
}

//设定给定序号的元素值 
template <typename T>
void LinkedList<T>::Set(int index, const T& t)
{
	LinkedListNode<T> *linked_list_node = header_node_;
	for (int i = 0; i < index; ++i)
	{
		linked_list_node = linked_list_node->next_node;
	}
	linked_list_node->data = t;
}

//查询给定元素的序号
template <typename T>
int LinkedList<T>::Index(const T& t) const
{
	int index = 0;
	LinkedListNode<T> *linked_list_node = header_node_;
	while (linked_list_node->next_node != nullptr)
	{
		if (t == linked_list_node->data)
			return index;
		linked_list_node = linked_list_node->next_node;
		++index;
	}
	return list_size_; // index == list_size
}

//删除指定序号的节点
template <typename T>
void LinkedList<T>::Erase(int index)
{
	if (index >= list_size_ || index < 0)
		return;
	
	LinkedListNode<T> *temp_node = header_node_;
	if (0 == index)
	{
		header_node_ = header_node_->next_node;
		delete temp_node;
		--list_size_;
	}
	else
	{
		for (int i = 0; i < index-1; ++i)
		{
			temp_node = temp_node->next_node;
		}

		LinkedListNode<T> *temp_node1 = temp_node->next_node;
		temp_node->next_node = temp_node->next_node->next_node;
		delete temp_node1;
		--list_size_;
		if (nullptr == temp_node->next_node)
			end_node_ = temp_node;
	}
	if (0 == list_size_)
		header_node_ = end_node_ = nullptr;
}

//在指定序号中插入节点
template <typename T>
void LinkedList<T>::Insert(int index, const T& t)
{
	if (index > list_size_ || index < 0)
		return;

	LinkedListNode<T> *linked_list_node = new LinkedListNode<T>(t);
	if (0 == index)
	{
		linked_list_node->next_node = header_node_;
		header_node_ = linked_list_node;
		++list_size_;
	}
	else
	{
		LinkedListNode<T> *temp_node = header_node_;
		for (int i = 0; i < index - 1; ++i)
		{
			temp_node = temp_node->next_node;
		}

		linked_list_node->next_node = temp_node->next_node;
		temp_node->next_node = linked_list_node;
		++list_size_;
	}
}

//在链表尾端添加节点
template <typename T>
void LinkedList<T>::PushBack(const T& t)
{
	if (nullptr == header_node_)
	{
		LinkedListNode<T> *next_node = new LinkedListNode<T>(t);
		header_node_ = next_node;
		end_node_ = next_node;
		list_size_ = 1;
	}
	else
	{
		LinkedListNode<T> *next_node = new LinkedListNode<T>(t);
		end_node_->next_node = next_node;
		end_node_ = next_node;
		++list_size_;
	}
    //std::cout << "size:" << list_size_ << std::endl;
}

//给链表设定大小 如果设定大小大于当前大小 直接返回 
template <typename T>
void LinkedList<T>::SetSize(int size)
{
	if (list_size_ <= size)
		return;
	else
	{
		LinkedListNode<T> *linked_list_node = header_node_;
		for (int i = 0; i < size; ++i)
		{
			end_node_ = linked_list_node;
			linked_list_node = linked_list_node->next_node;
		}
		
		LinkedListNode<T> *next_node = linked_list_node->next_node;
		while (next_node != nullptr)
		{
			delete linked_list_node;
			linked_list_node = next_node;
			next_node = next_node->next_node;
		}
		delete linked_list_node;
		list_size_ = size;
		if (0 == list_size_)
			header_node_ = end_node_ = nullptr;
	}
}

//未完成
//template <typename T>
//void LinkedList<T>::RemoveRange(int from_index, int to_index)
//{
	/*if (from_index < 0 || from_index >= list_size_ || to_index <= 0 || to_index >list_size_ || from_index >= to_index)
		return;
	if (0 == from_index)
	{
		LinkedListNode<T> *link_list_node = header_node_;
		for (int i = 0; i < to_index; ++i)
		{
			link_list_node = link_list_node->next_node;
		}
		header_node_ = link_list_node;
		list_size_ -= (to_index - from_index);
		if (0 == list_size_)
			header_node_ = end_node_ = nullptr;
	}
	else
	{
		LinkedListNode<T> *link_list_node = header_node_;
		int i = 0;
		for (; i < from_index-1; ++i)
			link_list_node = link_list_node->next_node;
		LinkedListNode<T> *temp_node = link_list_node;
		for (; i < to_index; ++i)
			link_list_node = link_list_node->next_node;
	}*/
//}
#endif  //LINKED_LIST_H_

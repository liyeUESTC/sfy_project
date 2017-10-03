#ifndef FORWARD_COMMON_SINGLETON_H_
#define FORWARD_COMMON_SINGLETON_H_

template <typename T>
class Singleton
{
public:
    virtual  ~Singleton() {};
	static T *GetInstance()
	{
		if(nullptr == ptr_)
		{
			ptr_ = new T;
		}
		return ptr_;
	}
	static void Destroy()
	{
		if(nullptr != ptr_)
		{
			delete ptr_;
			ptr_ = nullptr;
		}
	}
protected:
    Singleton() {};
private:
	static T *ptr_;
	//cant't structure
//	Singleton() {};
//	~Singleton() {};
	//can't copy
	Singleton(const Singleton &singleton) {};
	Singleton & operator=(const Singleton &singleton) {};
};

template <typename T>
T* Singleton<T>::ptr_ = nullptr;
#endif  // FORWARD_COMMON_SINGLETON_H_

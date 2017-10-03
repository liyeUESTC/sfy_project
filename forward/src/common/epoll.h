#ifndef FORWARD_COMMON_EPOLL_H_
#define FORWARD_COMMON_EPOLL_H_

#include <sys/epoll.h>

#include "singleton.h"
#include "epoll_event.h"

class Epoll:public Singleton<Epoll>
{
public:
	Epoll():epoll_fd_(-1),epoll_size_(-1),epoll_events_(nullptr),finish_(false) {};
	~Epoll() {};
	int Init(int epoll_size);
	int EventCtl(int fd,EpollEvent* epoll_event,int op);
	void Run();
	int Recovery();
	void Finish();
private:
	int epoll_fd_;
	int epoll_size_;
	struct epoll_event *epoll_events_;
	bool finish_;
};
#endif  //FORWARD_COMMON_EPOLL_H_

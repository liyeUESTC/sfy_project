
#include "epoll_event.h"

#include <sys/epoll.h>

#include <iostream>

#include "epoll.h"
#include "base_define.h"

using namespace std;

//void EpollEvent::set_fd(int fd)
//{
//	fd_ = fd;
//}

//int EpollEvent::fd()
//{
//	return fd_;
//}
int EpollEvent::RegisterREvent(int fd)
{
	events_ = EPOLLIN;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_ADD) < 0)
	{
		cout << "AddWriteEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;		
}

int EpollEvent::RegisterWEvent(int fd)
{
	events_ = EPOLLOUT;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_ADD) < 0)
	{
		cout << "AddReadEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int EpollEvent::RegisterRWEvent(int fd)
{
	events_ = EPOLLIN | EPOLLOUT;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_ADD) < 0)
	{
		cout << "DeleteWriteEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int EpollEvent::UnregisterRWEvent(int fd)
{
	events_ = EPOLLIN | EPOLLOUT;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_DEL) < 0)
	{
		cout << "DeleteReadEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int EpollEvent::OpenREvent(int fd)
{
	events_ = events_ | EPOLLIN;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_MOD) < 0)
	{
		cout << "ChangeWriteEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}
int EpollEvent::OpenWEvent(int fd)
{
	events_ = events_ | EPOLLOUT;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_MOD) < 0)
	{
		cout << "ChangeReadEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int EpollEvent::CloseREvent(int fd)
{
	events_ = events_ & ~EPOLLIN;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_MOD) < 0)
	{
		cout << "ChangeReadEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int EpollEvent::CloseWEvent(int fd)
{
	events_ = events_ & ~EPOLLOUT;
	if(Epoll::GetInstance()->EventCtl(fd,this,EPOLL_CTL_MOD) < 0)
	{
		cout << "ChangeReadEvent error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

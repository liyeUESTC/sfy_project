#include "epoll.h"

#include <errno.h>
#include <string.h>
#include <unistd.h>

#include  <iostream>

#include "base_define.h"
#include "tcp_agent.h"
#include "agent_manager.h"


int Epoll::Init(int epoll_size)
{
	epoll_size_ = epoll_size;
	if((epoll_fd_ = epoll_create(epoll_size_)) < 0)
	{
		std::cout << "epoll_create error" << std::endl;
		return FAILED;
	}
		
	epoll_events_ = new struct epoll_event[epoll_size_];
	memset(epoll_events_,0,sizeof(struct epoll_event)*epoll_size_);
	return SUCCESSFUL;
}

int Epoll::EventCtl(int fd,EpollEvent* epoll_event,int op)
{
	struct epoll_event event;
	memset(&event,0,sizeof(struct epoll_event));
	event.data.ptr = epoll_event;
	event.events = epoll_event->events();
	if(epoll_ctl(epoll_fd_,op,fd,&event) < 0)
	{
		std::cout << "epoll_ctl error" << std::endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

void Epoll::Run()
{
	while(1)
	{
		int ready;
		if((ready = epoll_wait(epoll_fd_,epoll_events_,epoll_size_,5)) < 0)
		{
			if(EINTR == errno)
				continue;
			else
			{
				std::cout << "epoll_wait error" << std::endl;
				break;
			}
		}
		
     //   std::cout << "start epoll" << std::endl;
		for(int i = 0;i < ready;++i)
		{
			EpollEvent *epoll_event = (EpollEvent *)epoll_events_[i].data.ptr;
			if(epoll_event == nullptr)
			{
				std::cout << "epoll_event is nullptr" << std::endl;
				continue;
			}
        //    std::cout << epoll_event->agent_id() << std::endl;
			TcpAgent *agent = AgentManager::GetInstance()->Find(epoll_event->agent_id());
			
			if(nullptr == agent)
			{
				std::cout << "the agent is not find" << std::endl;
                continue;
			}
			
//            std::cout << "111" << std::endl;
			//epoll error
			if((epoll_events_[i].events & EPOLLERR) || (epoll_events_[i].events & EPOLLHUP))
			{
//                std::cout << "1" << std::endl;
                AgentManager::GetInstance()->RecoveryAgent(agent);
				continue;
			}
			
			if(epoll_events_[i].events & EPOLLOUT)
			{
              //  std::cout << "2" << std::endl;
				if(agent->connect_state() == kConnecting)
				{
//                    std::cout << "kConnecting" << std::endl;
					agent->CheckConnect();
					if(agent->connect_state() == kConnected)
					{
  //                      std::cout << "kConnected" << std::endl;
						if(agent->ConnectBack() == FAILED)
						{
//							std::cout << "ConnectBack error" << std::endl;
                            AgentManager::GetInstance()->RecoveryAgent(agent);
							continue;
						}
					}
				}
                if(agent->connect_state() == kConnected)
				{
           //         std::cout << "3" << std::endl;
          //          std::cout << "start send" << std::endl;
					if(agent->Send() == FAILED)
					{
                      //  std::cout << "errno:" << errno << std::endl;
//						std::cout << "Send error" << std::endl;
                        AgentManager::GetInstance()->RecoveryAgent(agent);
						continue;
					}
				}
			}
			
			else if(epoll_events_[i].events & EPOLLIN)
			{
				if(agent->connect_state() == kConnected)
				{
           //         std::cout << "4" << std::endl;
					if(agent->Receive() == FAILED)
					{
             //           std::cout <<"errno:" << errno << std::endl;
//						std::cout << "Receive error" << std::endl;
                        AgentManager::GetInstance()->RecoveryAgent(agent);
                        continue;
					}
                    agent->ReceiveBack();
             //       std::cout << "start receiveback" << std::endl;
				}
				
			}
		}
		AgentManager::GetInstance()->CleanAgent();
		if(finish_)
			break;
	}

}

int Epoll::Recovery()
{
	if(-1 != epoll_fd_)
		if(close(epoll_fd_) < 0)
			return FAILED;
	if(nullptr != epoll_events_)
	{
		delete [] epoll_events_;
		epoll_events_ = nullptr;
	}
	return SUCCESSFUL;
}

void Epoll::Finish()
{
	finish_ = true;
}



#include <iostream>

#include "base_define.h"
#include "epoll.h"
#include "tcp_socket_addr.h"
#include "tcp_server_agent.h"
#include "agent_manager.h"
#include "signal.h"


const int kEpollSize = 1024;

void MyExit(int signo)
{
    if(SIGINT == signo)
    {
        Epoll::GetInstance()->Finish();   
    }
}

int main(int argc,char *argv[])
{
	if(argc != 4 )
	{
        std::cout << "usage:" << argv[0] << "ip port connect_num" << std::endl;
		return FAILED;
	}
	
    if(signal(SIGINT,MyExit) == SIG_ERR)
    {
        std::cout << "can't catch SIGINT" << std::endl;
        return FAILED;
    }
	if(Epoll::GetInstance()->Init(kEpollSize) == FAILED)
	{
		std::cout << "Init error" << std::endl;
		return FAILED;
	}
	
	TcpSocketAddr tcp_socket_addr(argv[1],argv[2]);

	int connect_num;
	sscanf(argv[3],"%d",&connect_num);
	for(int i = 0;i < connect_num;++i)
	{
		TcpServerAgent *tcp_server_agent = AgentManager::GetInstance()->
			CreateAgent<TcpServerAgent>(tcp_socket_addr);
		tcp_server_agent->Init();
	}
	
	Epoll::GetInstance()->Run();
	
	Epoll::GetInstance()->Recovery();
	AgentManager::GetInstance()->CleanAllAgent();
    std::cout << "exit" << std::endl;
    return 0;
}


#include <iostream>

#include "base_define.h"
#include "tcp_socket_addr.h"
#include "agent_manager.h"
#include "epoll.h"
#include "tcp_listen_agent.h"
#include "signal.h"
#include "tcp_client_agent.h"

using namespace std;

const int kEpollSize = 2048;

void MyExit(int signo)
{
    if(SIGINT == signo)
    {
        Epoll::GetInstance()->Finish();
        cout << "start finish" << endl;
    }
}

int main(int argc,char *argv[])
{
	if(argc != 2 )
	{
		cout << "usage:" << argv[0] << " port" << endl;
		return FAILED;
	}
	
    if(signal(SIGINT,MyExit) == SIG_ERR)
    {
        cout << "can't canch SIGINT" << endl;
        return FAILED;
    }
	if(Epoll::GetInstance()->Init(kEpollSize) == FAILED)
	{
		cout << "Init error" << endl;
		return FAILED;
	}
	
	TcpSocketAddr tcp_socket_addr;
	tcp_socket_addr.set_port(argv[1]);
	TcpListenAgent<TcpClientAgent> *tcp_listen_agent = AgentManager::GetInstance()->CreateAgent<TcpListenAgent<TcpClientAgent> >(tcp_socket_addr);
	if(tcp_listen_agent == nullptr)
	{
		cout << "CreateAgent error" << endl;
		return FAILED;
	}
	if(tcp_listen_agent->Init() == FAILED)
	{
        cout << errno << endl;
		cout << "Init error" << endl;
		return FAILED;
	}
	
	Epoll::GetInstance()->Run();
	
	Epoll::GetInstance()->Recovery();
	AgentManager::GetInstance()->CleanAllAgent();

    cout << "exit" << endl;
	return 0;
}

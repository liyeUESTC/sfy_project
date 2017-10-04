#ifndef FORWARD_COMMON_TCPLISTENAGENT_H_
#define FORWARD_COMMON_TCPLISTENAGENT_H_

#include <iostream>

#include "tcp_agent.h"
#include "epoll_event.h"
#include "tcp_socket.h"

const int kListenNum = 2000;

template<typename T>
class TcpListenAgent:public TcpAgent
{
public:
	TcpListenAgent():TcpAgent(),client_num_(0) {};
	TcpListenAgent(const TcpSocketAddr &tcp_socket_addr):
	    TcpAgent(tcp_socket_addr) {};
	~TcpListenAgent() {};
	int Init();
	int Send();
	int Receive();
	int SendBack();
	int ReceiveBack();
private:
    int client_num_;
	//TcpSocket tcp_socket_;
	//EpollEvent epoll_event_;
};

template<typename T>
int TcpListenAgent<T>::Init()
{
	if((tcp_socket_.Socket() == FAILED) || 
		(tcp_socket_.SetNoBlock() == FAILED) || 
		(tcp_socket_.Bind()) == FAILED ||
		(tcp_socket_.Listen(kListenNum)) == FAILED)
	{
        std::cout << "tcpListen init error" << std::endl;
		return FAILED;
	}
	//epoll_event_.set_fd(tcp_socket_.sock_fd());
	//epoll_event_.set_agent_id(agent_id());
	if(epoll_event_.RegisterREvent(socket_fd()) == FAILED)
	{
        std::cout << "Tcplisten init error" << std::endl;
		return FAILED;
	}
    set_connect_state(kConnected);
	return SUCCESSFUL;
}

template<typename T>
int TcpListenAgent<T>::Receive()
{
	TcpSocketAddr tcp_socket_addr;
	int connected_fd;
	if((connected_fd =tcp_socket_.Accept(tcp_socket_addr)) == FAILED)
	{
        std::cout << "Receive error" << std::endl;
		return FAILED;
	}
	
	T* client_agent = AgentManager::GetInstance()->
		CreateAgent<T>(connected_fd,tcp_socket_addr);
	client_agent->Init();
//    cout << "客户端数量:" << ++client_num_ << endl;
	return SUCCESSFUL;
}

template<typename T>
int TcpListenAgent<T>::Send()
{
    return SUCCESSFUL;
}

template<typename T>
int TcpListenAgent<T>::SendBack()
{
    return SUCCESSFUL;
}

template<typename T>
int TcpListenAgent<T>::ReceiveBack()
{
    return SUCCESSFUL;
}
#endif

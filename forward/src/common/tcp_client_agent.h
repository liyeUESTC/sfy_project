#ifndef FORWARD_COMMON_TCPCLIENTAGENT_H_
#define FORWARD_COMMON_TCPCLIENTAGENT_H_

#include <time.h>
#include <string.h>

#include "tcp_work_agent.h"
#include "performance.h"



class TcpClientAgent:public TcpWorkAgent
{
public:
	TcpClientAgent():TcpWorkAgent() {};
//	TcpClientAgent(int connfd,const TcpSocketAddr &tcp_socket_addr):
//		tcp_socket_(connfd,tcp_socket_addr),writer_(tcp_socket_),
//		reader_(tcp_socket_) {};
    TcpClientAgent(int connfd,const TcpSocketAddr &tcp_socket_addr):
        TcpWorkAgent(connfd,tcp_socket_addr) {};
	int Init();
	//int Send();
	//int Receive();
	int SendBack();
	int ReceiveBack();
	void TestPerformance();
    static Performance performance_;
	//int SendReady(struct Msg &msg);
private:
	//TcpSocket tcp_socket_;
	//EpollEvent epoll_event_;
	//Buffer buffer_;
	//Writer writer_;
	//Reader reader_;

};

#endif //FORWARD_COMMON_TCPCLIENTAGENT_H_

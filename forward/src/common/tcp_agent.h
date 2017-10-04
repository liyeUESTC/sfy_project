#ifndef FORWARD_COMMON_AGENT_H_
#define FORWARD_COMMON_AGENT_H_

#include "tcp_socket.h"
#include "epoll_event.h"
#include "base_define.h"

const int kNoConnect = 0;
const int kConnecting = 1;
const int kConnected = 2;
const int kConnectFailed = 3;

class TcpAgent
{
public:
	TcpAgent():tcp_socket_(),epoll_event_(),connect_state_(kNoConnect)
    {}
    TcpAgent(const TcpSocketAddr &tcp_socket_addr):
        tcp_socket_(tcp_socket_addr),epoll_event_(),
        connect_state_(kNoConnect)
    {}
    TcpAgent(int connfd,const TcpSocketAddr &tcp_socket_addr):
        tcp_socket_(connfd,tcp_socket_addr),epoll_event_(),
        connect_state_(kNoConnect) 
    {};
	~TcpAgent() {};
	void set_agent_id(int agent_id)
	{
		epoll_event_.set_agent_id(agent_id);
	
	}
	int agent_id() const 
	{
		return epoll_event_.agent_id();
	}
    void set_socket_fd(int socket_fd)
    {
        tcp_socket_.set_socket_fd(socket_fd);
    } 
    int socket_fd() const
    {
        return tcp_socket_.socket_fd();
    }
	virtual int Init() = 0;
	void set_connect_state(int connect_state)
	{
		connect_state_ = connect_state;
	}
	int connect_state() const
	{
		return connect_state_;
	}

	virtual int Send();
	virtual int Receive();
	virtual int SendBack() ;
	virtual int ReceiveBack() ;
	virtual int CheckConnect();
    virtual int SendReady(const struct Msg &msg);
	virtual int ConnectBack();
    virtual int Close();
protected:
	TcpSocket tcp_socket_;
	EpollEvent epoll_event_;
	int connect_state_;
};

#endif

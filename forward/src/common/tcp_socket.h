#ifndef FARWARD_COMMOND_TCPSOCKET_H_
#define FARWARD_COMMOND_TCPSOCKET_H_

#include <sys/uio.h>
#include "tcp_socket_addr.h"

class TcpSocket
{
private:
	int socket_fd_;
	TcpSocketAddr tcp_socket_addr_;
	bool block_;
public:
    TcpSocket():socket_fd_(-1),block_(true) {}
	TcpSocket(int socket_fd):socket_fd_(socket_fd),block_(true) {};
    TcpSocket(const TcpSocketAddr &tcp_socket_addr):
		tcp_socket_addr_(tcp_socket_addr),block_(true) {}
	TcpSocket(int socket_fd,const TcpSocketAddr &tcp_socket_addr):
		socket_fd_(socket_fd),tcp_socket_addr_(tcp_socket_addr),block_(true) {}
	bool block()
	{
		return block_;
	}
    int Socket();
	int SetNoBlock();
    int Connect();
    int Bind();
	int Listen(int listen_num);
    int Accept(TcpSocketAddr &tcp_socket_addr);
	int Getsockopt();
	int Writev(const struct iovec *iovec,int iovcnt);
	int Read(char *buf,int count);
	int socket_fd()const
	{
		return socket_fd_;
	}
    void set_socket_fd(int socket_fd)
    {
        socket_fd_ = socket_fd;
    }
    int Close();
};

#endif  //FARWARD_COMMOND_TCPSOCKET_H_

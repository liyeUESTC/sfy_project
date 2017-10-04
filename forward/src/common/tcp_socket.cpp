#include "tcp_socket.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include <iostream>

#include "base_define.h"

using namespace std;

int TcpSocket::Socket()
{
	if((socket_fd_ = socket(AF_INET,SOCK_STREAM,0)) < 0) 
	{
		cout << "Socket::socket error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int TcpSocket::SetNoBlock()
{
	int flags;
	if((flags = fcntl(socket_fd_,F_GETFL,0)) < 0)
	{
		cout << "SetNoBlock::fcntl F_GETFL error" << endl;
		return FAILED;
	}
	flags |= O_NONBLOCK;
	if(fcntl(socket_fd_,F_SETFL,flags) < 0)
	{
		cout << "SetNoBlock::fcntl::F_SETFL error" << endl;
		return FAILED;
	}
	block_ = false;
	return SUCCESSFUL;
}

int TcpSocket::Connect()
{
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(tcp_socket_addr_.port());
	if(tcp_socket_addr_.IpIsAny())
		addr.sin_addr.s_addr = htonl(INADDR_ANY);  //閫氶厤鍦板潃
	else if(inet_pton(AF_INET,tcp_socket_addr_.ip().c_str(),&addr.sin_addr) <= 0)
	{
		cout << "Connect::inet_pton error" << endl;
		return FAILED;
	}

	if(connect(socket_fd_,(struct sockaddr *)&addr,sizeof(addr)) < 0)
	{
		if((block() == true) || ((block() == false) && (EINPROGRESS != errno)) )
		{
			cout << "Connect::connect error" << endl;
			return FAILED;
		}
	}
	return SUCCESSFUL;
}

int TcpSocket::Bind()
{
	struct sockaddr_in addr;
	memset(&addr,0,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(tcp_socket_addr_.port());
	if(tcp_socket_addr_.IpIsAny())
		addr.sin_addr.s_addr = htonl(INADDR_ANY);  //通配地址
	else if(inet_pton(AF_INET,tcp_socket_addr_.ip().c_str(),&addr.sin_addr) <= 0)
	{
		cout << "Connect::inet_pton error" << endl;
		return FAILED;
	}
	
	if(bind(socket_fd_,(struct sockaddr *)&addr,sizeof(addr)) < 0) //绑定地址
	{
		cout << "Bind::bind error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int TcpSocket::Listen(int listen_num)
{
	if(listen(socket_fd_,listen_num) < 0)
	{
		cout << "Listen::listen error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int TcpSocket::Accept(TcpSocketAddr &tcp_socket_addr)
{
	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t clilen = sizeof(cliaddr);

	if((connfd = accept(socket_fd_,(struct sockaddr *)&cliaddr,&clilen)) < 0)
	{
		if((block() == true) || ((block() == false) && (EWOULDBLOCK != errno)
			&&(ECONNABORTED != errno) && (EPROTO !=errno) && (EINTR != errno)))
		{
			cout << "Accept::accept error" << endl;
			return FAILED;
		}
	}

	tcp_socket_addr.set_port(ntohs( cliaddr.sin_port ));
	tcp_socket_addr.set_ip(inet_ntoa( cliaddr.sin_addr ));
	return connfd;
}

int TcpSocket::Close()
{
	if(socket_fd_ == -1)
		return SUCCESSFUL;
	else if(close(socket_fd_) < 0)
	{
         cout << "Close::close error" << endl;
		 return FAILED;
	}
	socket_fd_ = -1;
	return SUCCESSFUL;
}
int TcpSocket::Read(char *buf,int count)
{
	int read_size = 0;
	if((read_size = read(socket_fd_,buf,count)) < 0)
	{
		if((block() == true && EINTR != errno) || 
           (block() == false && EWOULDBLOCK != errno) )
        {
     //       cout << "1" << endl;
		    return FAILED;
        }
	}
    else if(0 == read_size)
    {
     //   cout << "2" << endl;
        return FAILED;
    }
   // cout << "success read" << endl;
	return read_size;
}

int TcpSocket::Writev(const struct iovec *iovec,int iovcnt)
{
	int writed_size = 0;
	if((writed_size = writev(socket_fd_,iovec,iovcnt)) < 0)
	{
		if((block() == true && EINTR != errno) || 
           (block() == false && EWOULDBLOCK != errno) ) 
		    return FAILED;
	}
	return writed_size;
}

int TcpSocket::Getsockopt()
{
	int error;
    socklen_t error_len = sizeof(error);
	if(getsockopt(socket_fd_,SOL_SOCKET,SO_ERROR,&error,&error_len) < 0)
	{
		cout << "getsockopt error" << endl;
		return FAILED;
	}
	if(error != 0)
		return FAILED;
	return SUCCESSFUL;
}

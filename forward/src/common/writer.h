#ifndef FORWARD_COMMON_WRITE_H_
#define FORWARD_COMMON_WRITE_H_

#include <sys/uio.h>
#include <vector>

#include "tcp_socket.h"
#include "base_define.h"


struct Iov
{
	struct iovec send_iovec;
	char *complete_iovec;
};
class Writer
{
public:
	Writer() {};
	Writer(const TcpSocket &tcp_socket):tcp_socket_(tcp_socket) {};
	~Writer() {};
    void set_socket_fd(int socket_fd)
    {
        tcp_socket_.set_socket_fd(socket_fd);
    }
    int socket_fd() const
    {
        return tcp_socket_.socket_fd();
    }
	int WriteToBuffer(const struct Msg &msg);
	int WriteIovec();
	bool BufferIsEmpty() const
	{
		return send_iov_list_.empty();
	}
	//int WriteBack();
private:
    std::vector<struct Iov> send_iov_list_;
	TcpSocket tcp_socket_;
};

#endif //FORWARD_COMMON_WRITE_H_

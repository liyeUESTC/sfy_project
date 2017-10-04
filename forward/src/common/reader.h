#ifndef FORWARD_COMMON_READER_H_
#define FORWARD_COMMON_READER_H_

#include "base_define.h"
#include "tcp_socket.h"

const int kMsgHeaderLength = sizeof(struct MsgHeader);

class Reader
{
public:
    Reader():new_package_(true),read_content_(false), 
        msg_header_offset_(0),msg_offset_(0),read_complete_msg_(false)
    {}
	Reader(const TcpSocket &tcp_socket);
	~Reader() {};
	int ReadToBuffer();
	int ReadHeader();
	int ReadContent();
    void set_socket_fd(int socket_fd)
    {
        tcp_socket_.set_socket_fd(socket_fd);
    }
    int socket_fd() const
    {
        return tcp_socket_.socket_fd();
    }
	bool read_complete_msg() const
	{
		return read_complete_msg_;
	}
	struct Msg msg() const
	{
		return msg_;
	}
private:
	TcpSocket tcp_socket_;
	struct Msg msg_;
	bool new_package_;
	bool read_content_;
	int msg_header_offset_;
	int msg_offset_;
	bool read_complete_msg_;
};

#endif //FORWARD_COMMON_READER_H_

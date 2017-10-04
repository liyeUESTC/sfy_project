#ifndef FORWARD_COMMON_TCPAGENT_H_
#define FORWARD_COMMON_TCPAGENT_H_

#include "writer.h"
#include "reader.h"
#include "tcp_agent.h"

class TcpWorkAgent:public TcpAgent
{
public:
    TcpWorkAgent():TcpAgent(),writer_(),reader_() {}
    TcpWorkAgent(const TcpSocketAddr &tcp_socket_addr):
        TcpAgent(tcp_socket_addr),writer_(),reader_()
    {}

    TcpWorkAgent(int connfd,const TcpSocketAddr &tcp_socket_addr):
        TcpAgent(connfd,tcp_socket_addr),writer_(connfd),reader_(connfd)
    {}

    ~TcpWorkAgent() {}

    int Send();
    int Receive();
    int SendReady(const struct Msg &msg);
    void set_writer(int socket_fd)
    {
        writer_.set_socket_fd(socket_fd);
    }
    void set_reader(int socket_fd)
    {
        reader_.set_socket_fd(socket_fd);
    }
protected:
    Writer writer_;
    Reader reader_;
};
#endif

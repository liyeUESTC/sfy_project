#ifndef FORWARD_COMMON_TCPSERVERAGENT_H_
#define FORWARD_COMMON_TCPSERVERAGENT_H_

#include <vector>

#include "tcp_work_agent.h"


class TcpServerAgent:public TcpWorkAgent
{
public:
	TcpServerAgent():TcpWorkAgent() {};
    TcpServerAgent(const TcpSocketAddr &tcp_socket_addr)
        :TcpWorkAgent(tcp_socket_addr) {}
	~TcpServerAgent() {};
	int Init();
	int ConnectBack();
	//int Send();
	//int Receive();
	int SendBack();
	int ReceiveBack();
    int CheckConnect();
	static std::vector<int> pair_vec_;
	//int SendReady(struct Msg &msg);
private:
	//Writer writer_;
	//Reader reader_;
};

#endif //FORWARD_COMMON_TCPSERVERAGENT_H_

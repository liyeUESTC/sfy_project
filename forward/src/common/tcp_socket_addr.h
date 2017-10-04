#ifndef FORWARD_COMMON_TCPSOCKETADDR
#define FORWARD_COMMON_TCPSOCKETADDR

#include <string>

using  std::string;

const string kIpAddrAny = "0.0.0.0";
const int kPortAny = 0;

class TcpSocketAddr
{
private:
    int port_;
    string  ip_;
public:
    TcpSocketAddr():ip_(kIpAddrAny),port_(kPortAny) {};
    TcpSocketAddr(const char *ip,const char *port);
	TcpSocketAddr(const char *ip,int port);
    int port() const
    {
        return port_;
    }
    string ip() const
    {
        return ip_;
    }
    int set_port(const char* port);
	void set_port(int port);
    void set_ip(const char *ip);
	bool IpIsAny() const;
	bool PortIsAny() const;
};

#endif  //FORWARD_COMMON_TCPSOCKETADDR

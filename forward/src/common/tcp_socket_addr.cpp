#include "tcp_socket_addr.h"

#include "base_define.h"


TcpSocketAddr::TcpSocketAddr(const char *ip,const char *port)
{
    set_ip(ip);
    set_port(port);
}

TcpSocketAddr::TcpSocketAddr(const char *ip,int port)
{
	set_ip(ip);
	set_port(port);
}

int TcpSocketAddr::set_port(const char* port)
{
    int ret = sscanf(port,"%d",&port_);
    if(ret)
        return SUCCESSFUL;
    return FAILED;
}

void TcpSocketAddr::set_port(int port)
{
    port_ = port;
}

void TcpSocketAddr::set_ip(const char *ip)
{
    ip_ = string(ip);
}

bool TcpSocketAddr::IpIsAny() const
{
	if(kIpAddrAny == ip_)
		return true;
	return false;
}

bool TcpSocketAddr::PortIsAny() const
{
	if(kPortAny == port_)
		return true;
	return false;
}

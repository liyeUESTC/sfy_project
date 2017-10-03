
#include "tcp_agent.h"

#include <iostream>

#include "base_define.h"


int TcpAgent::Send()
{
    return SUCCESSFUL;
}

int TcpAgent::Receive()
{
    return SUCCESSFUL;
}

int TcpAgent::CheckConnect()
{
	
	return SUCCESSFUL;
}

int TcpAgent::ConnectBack()
{
	return SUCCESSFUL;
}

int TcpAgent::SendBack()
{
    return SUCCESSFUL;
}

int TcpAgent::ReceiveBack()
{
    return SUCCESSFUL;
}
int TcpAgent::SendReady(const struct Msg &msg)
{
    return SUCCESSFUL;
}
int TcpAgent::Close()
{
   if(tcp_socket_.Close() == FAILED)
       return FAILED;
   return SUCCESSFUL;
}

#include "tcp_work_agent.h"

#include <iostream>

#include "base_define.h"
#include "epoll_event.h"

int TcpWorkAgent::Send()
{
    if(writer_.WriteIovec() == FAILED)
	{
        std::cout << "Send error" << std::endl;
		return FAILED;
	}
	if(writer_.BufferIsEmpty())
	{
		if(epoll_event_.CloseWEvent(socket_fd()) == FAILED)
		{
            std::cout << "TcpClientAgent init error" << std::endl;
			return FAILED;
		} 
	}
	return SUCCESSFUL;
}

int TcpWorkAgent::Receive()
{
    if(reader_.ReadToBuffer() == FAILED)
	{
//		cout << "Receive error" << endl;
		return FAILED;
	}
	return SUCCESSFUL;
}

int TcpWorkAgent::SendReady(const struct Msg &msg)
{
	writer_.WriteToBuffer(msg);
	if(epoll_event_. OpenWEvent(socket_fd()) == FAILED)
	{
        std::cout << "startSend error" << std::endl;
		return FAILED;
	}
	return SUCCESSFUL;

}

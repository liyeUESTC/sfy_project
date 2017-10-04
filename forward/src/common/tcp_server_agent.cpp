#include "tcp_server_agent.h"

#include <string.h>

#include <iostream>


std::vector<int> TcpServerAgent::pair_vec_ = std::vector<int>();
int TcpServerAgent::Init()
{
	if((tcp_socket_.Socket() == FAILED) || 
		(tcp_socket_.SetNoBlock() == FAILED) ||
		(tcp_socket_.Connect() == FAILED))
	{
		std::cout << "Init error" << std::endl;
		return FAILED;
	}
	
	if(epoll_event_.RegisterWEvent(socket_fd()) == FAILED)
	{
		std::cout << "TcpClientAgent init error" << std::endl;
		return FAILED;
	}
    set_writer(socket_fd());
    set_reader(socket_fd());
    set_connect_state(kConnecting);
	return SUCCESSFUL;
}

int TcpServerAgent::ConnectBack()
{
	struct Msg msg;
	memset(&msg,0,sizeof(struct Msg) );
	msg.msg_header.cmd = kRequestId;
	msg.msg_header.length = 0;
	msg.msg_header.dst_id = epoll_event_.agent_id();
	if(SendReady(msg) == FAILED)
	{
		std::cout << "ReceiveBack error" << std::endl;
		return FAILED;
	}
	if(epoll_event_.OpenREvent(socket_fd()) == FAILED)
	{
		std::cout << "TcpClientAgent init error" << std::endl;
		return FAILED;
	} 
	return SUCCESSFUL;
}

int TcpServerAgent::SendBack()
{
	return SUCCESSFUL;
}

int  TcpServerAgent::ReceiveBack()
{
	if(reader_.read_complete_msg())
	{
    //    std::cout << "into receiveback" << std::endl;
		struct Msg msg = reader_.msg();
    //    std::cout << "get msg" << std::endl;
		switch(msg.msg_header.cmd)
		{
			case kReturnId:
			{
         //       std::cout << "return id" << std::endl;
				TcpServerAgent::pair_vec_.push_back(msg.msg_header.dst_id);
				if(TcpServerAgent::pair_vec_.size() == 2)
				{
                    char *buf = new char[kDataSize];
                    memset(buf,1,kDataSize);
					struct Msg send_msg;
					memset(&send_msg,0,sizeof(struct Msg) );
					send_msg.msg_header.cmd = kForwardMsg;
					send_msg.msg_header.length = kDataSize;
					send_msg.msg_header.src_id = TcpServerAgent::pair_vec_[1];
					send_msg.msg_header.dst_id = TcpServerAgent::pair_vec_[0];
					send_msg.data = buf;
					
					TcpServerAgent::pair_vec_.clear();
					
					if(SendReady(send_msg) == FAILED)
					{
						std::cout << "ReceiveBack error" << std::endl;
                        delete [] buf;
						return FAILED;
					}
                    delete [] buf;
        //            std::cout <<"start forward" << std::endl;
				}
				break;
			}
			case kForwardMsg:
			{
//                std::cout << msg.data << std::endl;
				int temp_id = msg.msg_header.src_id;
				msg.msg_header.src_id = msg.msg_header.dst_id;
				msg.msg_header.dst_id = temp_id;
				
				if(SendReady(msg) == FAILED)
				{
					std::cout << "ReceiveBack error" << std::endl;
					return FAILED;
				}
				
				break;
			}
			default:
				std::cout << "cmd error" << std::endl;
		}
	}
}

int TcpServerAgent::CheckConnect()
{
    if(tcp_socket_.Getsockopt() == FAILED)
    {
        set_connect_state(kConnectFailed);
        std::cout << "Getsockopt error" << std::endl;
        return FAILED;
    }

    set_connect_state(kConnected);
    return SUCCESSFUL;
}

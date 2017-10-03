#include <string.h>
#include <sys/time.h>

#include <iostream>

#include "tcp_client_agent.h"
#include "base_define.h"
#include "agent_manager.h"

using namespace std;

Performance TcpClientAgent::performance_= Performance();

int TcpClientAgent::Init()
{
	//epoll_event_.set_fd(tcp_socket_.sock_fd());
	//epoll_event_.set_agent_id(agent_id());
	
	if(epoll_event_.RegisterREvent(socket_fd()) == FAILED)
	{
		cout << "TcpClientAgent init error" << endl;
		return FAILED;
	}
    
    set_writer(socket_fd());
    set_reader(socket_fd());
    set_connect_state(kConnected);
	return SUCCESSFUL;
}
// /* /* int TcpClientAgent::StartSend(struct Msg &msg)
// {
	// writer_.WriteToBuffer(msg);
	// if(epoll_event_.ChangeWriteEvent() == FAILED)
	// {
		// cout << "startSend error" << endl;
		// return FAILED;
	// }
	// return SUCCESSFUL;
// } */ */
// int TcpClientAgent::Send()
// {
	// if(writer_.WriteIovec() == FAILED)
	// {
		// cout << "Send error" << endl;
		// return FAILED
	// }
	// return SUCCESSFUL;
// }

// int TcpClientAgent::Receive()
// {
	// if(reader_.ReadToBuffer() == FAILED)
	// {
		// cout << "Receive error" << endl;
		// return FAILED;
	// }
	// return SUCCESSFUL;
// }

int TcpClientAgent:: SendBack()
{
	return SUCCESSFUL;
}

int TcpClientAgent::ReceiveBack()
{
	if(reader_.read_complete_msg())
	{
		struct Msg msg = reader_.msg();
		switch(msg.msg_header.cmd)
		{
			case kRequestId:
			{
//                cout << "request id" << endl;
				struct Msg send_msg;
				memset(&send_msg,0,sizeof(struct Msg) );
				send_msg.msg_header.cmd = kReturnId;
				send_msg.msg_header.length = 0;
				send_msg.msg_header.dst_id = epoll_event_.agent_id();
				if(SendReady(send_msg) == FAILED)
				{
					cout << "ReceiveBack error" << endl;
					return FAILED;
				}
				break;	
			}
			case kForwardMsg:
			{
			    performance_.PerformanceCount(kDataSize+kMsgHeaderSize);
  //              cout << "receive forward msg" << endl;
            //    cout << msg.data << endl;
				uint32_t dst_id = msg.msg_header.dst_id;
				TcpAgent *agent = AgentManager::GetInstance()->Find(dst_id);
				if(nullptr == agent)
				{
					cout << "ReceiveBack error" << endl;
					return FAILED;
				}
				if(agent->SendReady(msg) == FAILED)
				{
					cout << "ReceiveBack error" << endl;
					return FAILED;
				}
				break;
			}
			default:
				cout << "cmd error" << endl;
		}
	}
}



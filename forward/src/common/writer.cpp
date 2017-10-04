#include "writer.h"

#include <string.h>
#include <limits.h>

#include <iostream>

#include "base_define.h"

using namespace std;

int Writer::WriteToBuffer(const struct Msg &msg)
{
	char *send_msg = new char[sizeof(struct MsgHeader)+msg.msg_header.length];
	memcpy(send_msg,&msg.msg_header,sizeof(struct MsgHeader));
	memcpy(send_msg+sizeof(struct MsgHeader),msg.data,msg.msg_header.length);
	
	struct Iov msg_iov;
	memset(&msg_iov,0,sizeof(msg_iov));
	msg_iov.complete_iovec = send_msg;
	msg_iov.send_iovec.iov_base = send_msg;
	msg_iov.send_iovec.iov_len = sizeof(struct MsgHeader) + msg.msg_header.length;
	
	send_iov_list_.push_back(msg_iov);
	return SUCCESSFUL;
}

int Writer::WriteIovec()
{
	int iovcnt = send_iov_list_.size();
	if(iovcnt > IOV_MAX)
		iovcnt = IOV_MAX;
	struct iovec *send_iovec = new struct iovec[iovcnt];
	int i = 0;
	for(auto iter = send_iov_list_.begin();iter != send_iov_list_.end();
		++iter)
	{
		if(i >= iovcnt)
			break;
		send_iovec[i] = iter->send_iovec;
		++i;
	}
	
	int writed_size = 0;
	if((writed_size = tcp_socket_.Writev(send_iovec,iovcnt)) == FAILED)
	{
		cout << "write error" << endl;
		return FAILED;
	}	
	
	delete [] send_iovec;
	for(auto iter = send_iov_list_.begin();iter != send_iov_list_.end();)
	{
		if(writed_size >= iter->send_iovec.iov_len)
		{
			delete [] iter->complete_iovec;
			writed_size -= iter->send_iovec.iov_len;
			iter = send_iov_list_.erase(iter);
		}
		else
		{
			iter->send_iovec.iov_base += writed_size;
			iter->send_iovec.iov_len  -= writed_size;
			break;
		}
	}
	return SUCCESSFUL;
}

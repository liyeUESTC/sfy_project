
#include <string.h>

#include <iostream>

#include "reader.h"

using namespace std;

Reader::Reader(const TcpSocket &tcp_socket):new_package_(true),read_content_(false),msg_header_offset_(0),
				msg_offset_(0),read_complete_msg_(false),tcp_socket_(tcp_socket)
{
	memset(&msg_,0,sizeof(struct Msg));
}

int Reader::ReadToBuffer()
{
   // cout << "start read" << endl;
	if(new_package_)
	{
   //     cout << " start read header" << endl;
		if(ReadHeader() == FAILED)
		{
//			cout << "ReadToBuffer error" << endl;
			return FAILED;
		}
    //    cout << "read header successful" << endl;
	}
	
	if(read_content_)
	{
		if(ReadContent() == FAILED)
		{
//			cout << "ReadToBuffer error" << endl;
			return FAILED;
		}
	}
	return SUCCESSFUL;
}

int Reader::ReadHeader()
{	
	read_complete_msg_ = false;
	
	int read_size;
	if((read_size = tcp_socket_.Read((char *)(&msg_.msg_header+msg_header_offset_),
		kMsgHeaderLength-msg_header_offset_)) == FAILED)
	{
//		cout << "ReadHeader error" << endl;
		return FAILED;
	}
	
	msg_header_offset_ += read_size;
	
	if(msg_header_offset_ == kMsgHeaderLength)
	{
		new_package_ = false; 
		read_content_ = true;
		msg_header_offset_ = 0;
		msg_offset_ = 0;
        if(msg_.data != nullptr)
        {
            delete [] msg_.data;
            msg_.data = nullptr;
        }
        msg_.data = new char [msg_.msg_header.length];
		return SUCCESSFUL;
	}
	
	return SUCCESSFUL;
}

int Reader::ReadContent()
{
	int read_size = 0;
    if(msg_.msg_header.length == 0)
    {

		new_package_ = true;
		read_content_ = false;
		msg_header_offset_ = 0;
		msg_offset_ = 0;
		read_complete_msg_ = true;
 //       cout << "read successful" << endl;
		return SUCCESSFUL;
    }

     if((read_size = tcp_socket_.Read(msg_.data+msg_offset_,
		 msg_.msg_header.length-msg_offset_)) == FAILED)
	{
//	    cout << "Read error" << endl;
	    return FAILED;
    }
	
	msg_offset_ += read_size;
	if(msg_offset_ == msg_.msg_header.length)
	{
		new_package_ = true;
		read_content_ = false;
		msg_header_offset_ = 0;
		msg_offset_ = 0;
		read_complete_msg_ = true;
 //       cout << "read successful" << endl;
		return SUCCESSFUL;
	}
	return SUCCESSFUL;
}

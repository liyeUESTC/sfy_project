#ifndef FORWARD_COMMON_EPOLLEVENT_H_
#define FORWARD_COMMON_EPOLLEVENT_H_

#include <stdint.h>

class EpollEvent
{
public:
	EpollEvent():agent_id_(-1),events_(0) {};
	~EpollEvent() {};
	void set_agent_id(int agent_id)
	{
		agent_id_ = agent_id;
	}
	int agent_id()const
	{
		return agent_id_;
	}
    void set_events(int events)
    {
        events_ = events;
    }
    int events() const
    {
        return events_;
    }
	//void set_fd(int fd);
	//int fd();
	int RegisterREvent(int fd);
	int RegisterWEvent(int fd);
	int RegisterRWEvent(int fd);
	int UnregisterRWEvent(int fd);
	int OpenREvent(int fd);
	int OpenWEvent(int fd);
	int CloseREvent(int fd);
	int CloseWEvent(int fd);
private:
	int agent_id_;
	uint32_t events_;
	//int fd_;
};

#endif //FORWARD_COMMON_EPOLLEVENT_H_

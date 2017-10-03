#ifndef FORWARD_COMMON_AGENTMANAGER_H_
#define FORWARD_COMMON_AGENTMANAGER_H_

#include <vector>
#include <map>

#include <ext/hash_map>

#include "singleton.h"
#include "tcp_agent.h"
#include "tcp_socket_addr.h"


class AgentManager:public Singleton<AgentManager>
{
public:
	AgentManager():agent_id_(-1) {};
	~AgentManager() {};
	TcpAgent *Find(int agent_id);
	int RecoveryAgent(TcpAgent *agent);
	int CleanAgent();
	int CleanAllAgent();
	template<typename T>
    T* CreateAgent();
	template<typename T>
    T* CreateAgent( const TcpSocketAddr &tcp_socket_addr);
    template<typename T>
    T* CreateAgent(int connfd,const TcpSocketAddr &tcp_socket_addr );
private:
    __gnu_cxx::hash_map<int,TcpAgent *> agent_map_;
    std::vector<TcpAgent *> agent_recovery_vec_;
	int AddAgent(TcpAgent *agent);
	int agent_id_;
	int GenerateId()
	{
		++agent_id_;       
		return agent_id_;
	}
};

template<typename T>
T* AgentManager::CreateAgent()
{
	T *agent;
	agent = new T();
	if(agent != nullptr)
	{
		AddAgent(agent);
	}
	return agent;
} 

template<typename T>
T *AgentManager::CreateAgent(const TcpSocketAddr &tcp_socket_addr)
{
	T *agent;
	agent = new T(tcp_socket_addr);
	if(agent != nullptr)
	{
		AddAgent(agent);
	}
	return agent;
}

template<typename T>
T* AgentManager::CreateAgent(int connfd,const TcpSocketAddr &tcp_socket_addr)
{
	T *agent;
	agent = new T(connfd,tcp_socket_addr);
	if(agent != nullptr)
	{
		AddAgent(agent);
	}
	return agent;
}

#endif //FORWARD_COMMON_AGENTMANAGER_H_

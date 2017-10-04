
#include "agent_manager.h"

#include <iostream>


int AgentManager::AddAgent(TcpAgent *agent)
{
	int id = GenerateId();
    agent->set_agent_id(id);
//	agent_map_[id] = agent;
    agent_map_.insert(std::make_pair(id,agent));
//    std::cout << agent_map_.max_size() << std::endl;
	return SUCCESSFUL;
}

TcpAgent *AgentManager::Find(int agent_id)
{
	TcpAgent * agent = nullptr; 
	auto iter = agent_map_.find(agent_id);
	if(iter != agent_map_.end() )
		agent = iter->second;
	return agent;
}

int AgentManager::RecoveryAgent(TcpAgent *agent)
{
	int agent_id = agent->agent_id();
	if(agent_map_.erase(agent_id) == 0)
	{
		std::cout << "not find the agent" << std::endl;	
		return FAILED;
	}
	agent_recovery_vec_.push_back(agent);
	return SUCCESSFUL;
}

int AgentManager::CleanAgent()
{
	for(auto iter = agent_recovery_vec_.begin();iter != agent_recovery_vec_.end();
		++iter)
	{
        (*iter)->Close();
		delete *iter;
	}
	agent_recovery_vec_.clear();
	return SUCCESSFUL;
}

int AgentManager::CleanAllAgent()
{
	CleanAgent();
	for(auto iter = agent_map_.begin();iter != agent_map_.end();++iter)
	{
		delete iter->second;
	}
	agent_map_.clear();
	return SUCCESSFUL;
}

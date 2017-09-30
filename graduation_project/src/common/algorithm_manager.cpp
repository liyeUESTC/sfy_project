#include "algorithm_manager.h"


void AlgorithmManager::AddAlgorithm(Algorithm *algorithm)
{
	algorithm_vec_.push_back(algorithm);
}

void AlgorithmManager::Run()
{
	for(auto iter = algorithm_vec_.begin();iter != algorithm_vec_.end();++iter)
	{
		(*iter)->Run();
	}
}

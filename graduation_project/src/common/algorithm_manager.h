
#include <vector>

#include "algorithm.h"
#include "singleton.h"

class AlgorithmManager:public Singleton<AlgorithmManager>
{
public:
	AlgorithmManager() {};
	~AlgorithmManager() {};
	void AddAlgorithm(Algorithm *algorithm);
	void Run();
private:
	std::vector<Algorithm *> algorithm_vec_;
};

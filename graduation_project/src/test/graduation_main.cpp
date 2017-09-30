
#include <iostream>

#include "radar_pulse_manager.h"
#include "base_define.h"
#include "sdif_algorithm.h"
#include "pri_algorithm.h"
#include "file_save_manager.h"
#include "algorithm_manager.h"
#include "cdif_algorithm.h"
#include "grid_density_cluster.h"

using namespace std;

int main(int argc,char* argv[])
{
    if(argc != 2)
    {
        cout << "usage::" << argv[0] << "  config_file" << endl;
        return FAILED;
    }
    RadarPulseManager *radar_pulse_manager = RadarPulseManager::GetInstance();
    if(radar_pulse_manager->Init(argv[1]) == FAILED)
    {
        cout << "Init error" << endl;
        return FAILED;
    }
    if(radar_pulse_manager->Generate() == FAILED)
    {
        cout << "Generate FAILED" << endl;
        return FAILED;
    }
    
    vector<struct PulseDescribeWord> &pdw_vec =radar_pulse_manager->pdw_vec();

    AlgorithmManager *algorithm_manager = AlgorithmManager::GetInstance();
//    CDIFAlgorithm cdif_algorithm(pdw_vec,100.0,kCDIFParam);
//    algorithm_manager->AddAlgorithm(&cdif_algorithm);
//    SDIFAlgorithm sdif_algorithm(pdw_vec,100.0,pdw_vec.size(),kSDIFParam1,kSDIFParam2);
//    algorithm_manager->AddAlgorithm(&sdif_algorithm);
    PRIAlgorithm pri_algorithm(pdw_vec,100.0,kPRIParam1,kPRIParam2,kPRIParam3);
    algorithm_manager->AddAlgorithm(&pri_algorithm);
//    GridDensityCluster grid_density_cluster(pdw_vec);
//    algorithm_manager->AddAlgorithm(&grid_density_cluster);

    algorithm_manager->Run();

    FileSaveManager::GetInstance()->SaveFile();

    RadarPulseManager::Destroy();
    AlgorithmManager::Destroy();
    FileSaveManager::Destroy();

    return SUCCESSFUL;
}

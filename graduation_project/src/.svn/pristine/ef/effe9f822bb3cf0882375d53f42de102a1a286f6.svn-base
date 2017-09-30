#ifndef GRADUATION_SRC_COMMON_GRIDDENSITYCLUSTER_H_
#define GRADUATION_SRC_COMMON_GRIDDENSITYCLUSTER_H_

#include "algorithm.h"

struct Grid
{
    Grid():is_visit(false),class_num(-1) 
    {}
    ~Grid() {}
    std::vector<PulseDescribeWord> pdw_vec;
    bool is_visit;
    int class_num;
};

class GridDensityCluster:public Algorithm
{
public:
    GridDensityCluster(const std::vector<struct PulseDescribeWord> &pdw_vec);
    ~GridDensityCluster();
    void Normalization();
    void RemoveAcnode();
    void GridDivide();
    void Cluster();
    void HighDensityGridCluster();
    void LowDensityGridCluster();
    void DepthFirstSearch(int position);
    int Run();
    std::vector<std::vector<struct PulseDescribeWord>> &cluster_result()
    {
        return cluster_result_;
    }
private:
    std::vector<struct Grid> grid_vec_; 
    std::vector<std::vector<struct PulseDescribeWord>> cluster_result_;
    int grid_length_;
    int grid_num_;
    double density_threshold_;   
};
#endif  // GRADUATION_SRC_COMMON_GRIDDENSITYCLUSTER_H_


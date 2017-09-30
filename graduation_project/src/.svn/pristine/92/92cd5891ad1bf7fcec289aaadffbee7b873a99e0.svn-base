
#include "grid_density_cluster.h"

#include <math.h>

#include <iostream>

GridDensityCluster::GridDensityCluster(const std::vector<struct PulseDescribeWord> &pdw_vec)
    :Algorithm(pdw_vec)
{
    grid_length_ = pow(pdw_vec_.size(),1.0/3.0);
    grid_num_ = pow(grid_length_,3);
    density_threshold_ = 0;
}

GridDensityCluster::~GridDensityCluster()
{}

void GridDensityCluster::Normalization()
{
   for(auto iter = pdw_vec_.begin();iter != pdw_vec_.end();++iter)
   {
        iter->doa = (iter->doa - kMinDoa)/(kMaxDoa - kMinDoa);
        iter->rf = (iter->rf - kMinRf)/(kMaxRf - kMinRf);
        iter->pw = (iter->pw - kMinPw)/(kMaxPw - kMinPw);

   }
}

void GridDensityCluster::RemoveAcnode()
{
    std::vector<double> distance_sum_vec;
    double distance_mean = 0.0;
    for(auto iter1 = pdw_vec_.begin();iter1 != pdw_vec_.end();++iter1)
    {
        double distance_sum = 0.0;
        for(auto iter2 = pdw_vec_.begin();iter2 != pdw_vec_.end();++iter2)
        {
            double distance = sqrt(pow(iter1->doa-iter2->doa,2)+pow(iter1->rf-iter2->rf,2)
                    +pow(iter1->pw-iter2->pw,2));
            distance_sum += distance;
        }
        distance_sum_vec.push_back(distance_sum);
        distance_mean += distance_sum;
    }

    distance_mean /= pdw_vec_.size();
    int i = 0;
    for(auto iter = pdw_vec_.begin();iter != pdw_vec_.end();++i)
    {
        if(distance_sum_vec[i] >= distance_mean)
        {
            std::cout << distance_sum_vec[i] << "  " << distance_mean << std::endl;
            iter = pdw_vec_.erase(iter);
        }
        else
        {
            ++iter;
        }
    }


}

void GridDensityCluster::GridDivide()
{
    double step_size = 1.0 / (double)grid_length_;

    grid_vec_.resize(grid_num_);
 
    for(auto iter = pdw_vec_.begin();iter != pdw_vec_.end();++iter)
    {
 //       std::cout << iter->doa << "  " << step_size << std::endl;
        int position = (int)(iter->doa/step_size) * grid_length_ * grid_length_ +
                       (int)(iter->rf/step_size) * grid_length_ +
                       (int)(iter->pw/step_size);
//        std::cout << position << std::endl;
        grid_vec_[position].pdw_vec.push_back(*iter);
    }

//    std::cout << "111" << std::endl;    
}

void GridDensityCluster::Cluster()
{
    int count = 0;
    int max_num = 0;
    for(auto iter = grid_vec_.begin();iter != grid_vec_.end();++iter)
    {
//        std::cout << iter->pdw_vec.size() << std::endl;
        if(iter->pdw_vec.size() != 0)
            ++count;
        if(iter->pdw_vec.size() > max_num)
            max_num = iter->pdw_vec.size();
    }

    int a = sqrt(max_num);
    int b = max_num+a,c = 0;
    double d = 0.0;
    for(int i = 1;i <= a;++i)
    {
        b -= a;
        c += b;
        d += (2*b-a);
    }

    density_threshold_ = d/2.0/ (double)(a-1)*(double)pdw_vec_.size()/(double)count/(double)c*(double)a;
  //  std::cout << density_threshold_ << std::endl;
    density_threshold_ = kDensityThreshold * density_threshold_;

    HighDensityGridCluster();

    LowDensityGridCluster();

   // std::cout << cluster_result_.size() << std::endl;
    std::cout << std::endl;
    for(auto iter = cluster_result_.begin();iter != cluster_result_.end();++iter)
    {
        for(auto iter1 = iter->begin();iter1 != iter->end();++iter1)
        {
            std::cout << iter1->doa << "  "
                      << iter1->rf << "  "
                      << iter1->pw << std::endl;
        }
        std::cout << std::endl;
    }
}

void GridDensityCluster::DepthFirstSearch(int position)
{
    if(true == grid_vec_[position].is_visit)
        return;

    grid_vec_[position].class_num = cluster_result_.size() - 1;
    grid_vec_[position].is_visit = true;       
    cluster_result_.back().insert(cluster_result_.back().end(),grid_vec_[position].pdw_vec.begin(),
            grid_vec_[position].pdw_vec.end());

    int temp_position = position - 1;
    if(temp_position >= 0 && false == grid_vec_[temp_position].is_visit &&
          grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);    
    }

    temp_position = position + 1;
    if( temp_position < grid_num_ && false == grid_vec_[temp_position].is_visit &&
           grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);
    } 

    temp_position = position - grid_length_;
    if(temp_position >= 0 && false == grid_vec_[temp_position].is_visit &&
            grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);
    }

    temp_position = position + grid_length_;
    if(temp_position < grid_num_ && false == grid_vec_[temp_position].is_visit &&
            grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);
    }

    temp_position = position - grid_length_*grid_length_;
    if(temp_position >= 0 && false == grid_vec_[temp_position].is_visit &&
            grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);
    }

    temp_position = position + grid_length_ * grid_length_;
    if(temp_position < grid_num_ && false == grid_vec_[temp_position].is_visit &&
            grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
    {
        DepthFirstSearch(temp_position);
    }
    return;
}

void GridDensityCluster::HighDensityGridCluster()
{
    for(int i = 0;i < grid_vec_.size();++i)
    {
        std::cout << grid_vec_[i].pdw_vec.size() << "  "
                  << density_threshold_ << std::endl;
        if(grid_vec_[i].pdw_vec.size() > density_threshold_ &&
                grid_vec_[i].is_visit == false)
        {
            std::vector<struct PulseDescribeWord> pulse_vec;
            cluster_result_.push_back(pulse_vec);
            DepthFirstSearch(i);
        }
    }
}

void GridDensityCluster::LowDensityGridCluster()
{ 
    for(int i = 0;i < grid_vec_.size();++i)
    {
        if(grid_vec_[i].pdw_vec.size() <= density_threshold_)
        {
            int temp_position = i - 1;
            if(temp_position >= 0 && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num;
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());
            }

            temp_position = i + 1;
            if(temp_position < grid_num_ && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num;
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());

            }

            temp_position = i - grid_length_;
            if(temp_position > 0 && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num;    
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());

            }

            temp_position = i + grid_length_;
            if(temp_position < grid_num_ && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num; 
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());

            }

            temp_position = i - grid_length_ * grid_length_;
            if(temp_position > 0 && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num;    
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());

            }

            temp_position = i + grid_length_ * grid_length_;
            if(temp_position < grid_num_ && grid_vec_[temp_position].pdw_vec.size() > density_threshold_)
            {
                int position = grid_vec_[temp_position].class_num;   
                cluster_result_[position].insert(cluster_result_[position].end(),
                        grid_vec_[i].pdw_vec.begin(),grid_vec_[i].pdw_vec.end());

            }
        }
    }

}

int GridDensityCluster::Run()
{
    Normalization();
//    RemoveAcnode();
    GridDivide();
    Cluster();
}

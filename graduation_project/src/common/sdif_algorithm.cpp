
#include "sdif_algorithm.h"

#include <math.h>

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <list>

#include "file_save_manager.h"

SDIFAlgorithm::SDIFAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
                            double sample_time,int pulse_sum,
                            double sdif_param1,double sdif_param2)
                            :Algorithm(pdw_vec),
                            sample_time_(sample_time),pulse_sum_(pulse_sum),
                            sdif_param1_(sdif_param1),sdif_param2_(sdif_param2)
{
}


int SDIFAlgorithm::Run()
{
    for(int level = 1;level < kSDIFMaxOrder;++level)
    {
        if(pdw_vec_.size()/level < 5)
        {
            std::cout << "data is little" << std::endl;
            return SUCCESSFUL;
        }

        std::vector<double> pri_vec = PriMeasure(level);
        if(pri_vec.size() != 0)
		{
			if(1 == level)
			{
				if(1 == pri_vec.size() && PDWDetection(pri_vec) == SUCCESSFUL)
				{
					level = 0;
                    pulse_sum_ = pdw_vec_.size();
				}
				else
					continue;
			}
			else
			{
				if(PDWDetection(pri_vec) == SUCCESSFUL)
				{
					level = 0;
                    pulse_sum_ = pdw_vec_.size();
				}
			}
		}
    }
	return SUCCESSFUL;
}


std::vector<double> SDIFAlgorithm::HistogramCalculate(int level) const
{
    std::map<double,int> cumulative_difference_map;
    for(int i = 0;i < pdw_vec_.size() - level;++i)
    {
        double toa = pdw_vec_[i+level].toa - pdw_vec_[i].toa;

        if(cumulative_difference_map.size() == 0)
            cumulative_difference_map[toa] = 1;
        else
        {
            auto iter = cumulative_difference_map.begin();
            for(;iter != cumulative_difference_map.end();++iter)
            {
                if(toa > (iter->first)*kSDIFMinToleranceValue && 
                        toa < (iter->first)*kSDIFMaxToleranceValue)
                {
                    ++iter->second;
                    break;
                }
            }
            if(iter == cumulative_difference_map.end())
                cumulative_difference_map[toa] = 1;
        }
    }

    std::vector<double> pri_vec;
    std::vector<LineData> file_data;
    std::cout << "第" << level << "级差值直方图" << std::endl;
    for(auto iter = cumulative_difference_map.begin();
            iter != cumulative_difference_map.end();++iter)
    {
        double threshold = sdif_param1_*(double)(pulse_sum_-level) * pow(kMathConstantE,
                -(iter->first * sdif_param2_*(double)pulse_sum_/sample_time_));
        std::cout << iter->first << "   " << iter->second
                  << "   " << threshold 
                  << std::endl;

        LineData line_data;
        line_data.push_back(iter->first);
        line_data.push_back(iter->second);
        line_data.push_back(threshold);
        file_data.push_back(line_data);

        if(iter->second > threshold)
        {
            pri_vec.push_back(iter->first);
            std::cout << "find" << std::endl;
        }
    }

    std::string file_name = "SDIF" + ToStr(level) + "阶差值直方图.ouput";
    FileSaveManager::GetInstance()->AddFile(file_name,file_data);
    return pri_vec;
}

std::vector<double> & SDIFAlgorithm::SubharmonicCheck(std::vector<double> &pri_vec) const
{
    if(pri_vec.size() <= 1)
        return pri_vec;
    std::sort(pri_vec.begin(),pri_vec.end());
    std::cout << "start check" << std::endl;
    for(auto iter1 = pri_vec.begin();iter1 != pri_vec.end();++iter1)
    {
        auto iter2 = iter1;
        ++iter2;
        for(;iter2 != pri_vec.end();)
        {
            double pri_times = (*iter2) /(*iter1);
            std::cout << *iter1 <<"  " << *iter2 << std::endl;
            std::cout << "pri_times:" << pri_times << std::endl;
            int pri_times_int = pri_times; 
            if((pri_times - pri_times_int <= 0.5 && 
                pri_times <= pri_times_int * kSDIFMaxToleranceValue) || 
                (pri_times - pri_times_int > 0.5 &&
                 pri_times >= (pri_times_int+1) * kSDIFMinToleranceValue))
            {
                iter2 = pri_vec.erase(iter2);
                std::cout << "check success" << std::endl; 
            }
            else
                ++iter2;
        }
    } 

    return pri_vec;
}
std::vector<double> SDIFAlgorithm::PriMeasure(int level) const
{
    std::vector<double> pri_vec = HistogramCalculate(level);
    pri_vec =SubharmonicCheck(pri_vec);
    return pri_vec;
}

int SDIFAlgorithm::PDWDetection(const std::vector<double> &pri_vec)
{
   if(pri_vec.size() == 0)
        return SUCCESSFUL;

    std::list<struct PulseDescribeWord> pdw_list;
    pdw_list.assign(pdw_vec_.begin(),pdw_vec_.end());
	bool is_separate = false;

    for(auto iter_pri = pri_vec.begin();iter_pri != pri_vec.end();++iter_pri)
    {
        for(auto iter1 = pdw_list.begin();iter1 != pdw_list.end();++iter1)
        {
            struct RadarData radar_data;
            radar_data.pri = *iter_pri;
            bool is_find = false;
            auto standard_pdw = iter1;
            for(auto iter2 = pdw_list.begin();iter2 != pdw_list.end();++iter2)
            {
                if(false == is_find)
                {
                    if(iter2->toa - standard_pdw->toa < *iter_pri *kSDIFMinToleranceValue)
                        continue;
                    else if(iter2->toa - standard_pdw->toa >*iter_pri*kSDIFMaxToleranceValue)
                        break;
                    else
                    {
                        radar_data.pdw_vec.push_back(*standard_pdw); 
                        is_find = true;
                    }
                }
                if(true == is_find)
                {
                    double times = (iter2->toa - radar_data.pdw_vec.back().toa)/ (*iter_pri);
                    int times_int = times;
                    if((times - times_int <= 0.5 && times <= times_int*kSDIFMaxToleranceValue) ||
                        (times-times_int > 0.5 && times >= (times_int+1)*kSDIFMinToleranceValue))
                    {
                    //    if(iter2->toa-radar_data.pdw_vec.back().toa > *iter_pri*0.99 && iter2->toa-radar_data.pdw_vec.back().toa < *iter_pri*1.01)
                        radar_data.pdw_vec.push_back(*iter2);
                    }  
                }
            }
            if(radar_data.pdw_vec.size() > 5)
            {
				is_separate = true;
                std::cout << "匹配成功雷达数据" << std::endl
                     << "PRI:" << radar_data.pri << std::endl
                     << "TOA:";
                for(auto iter = radar_data.pdw_vec.begin();iter != radar_data.pdw_vec.end();++iter)
                {
                    std::cout << iter->toa << "   "; 
                    for(auto iter_list = pdw_list.begin();iter_list != pdw_list.end();)
                    {
                        if(iter_list->toa == iter->toa)
                        {
                            pdw_list.erase(iter_list);
                            break;
                        }
                        else
                            ++iter_list;
                    }
                }
                std::cout  << std::endl;
                char a;
                std::cin >> a;
                radar_data_vec_.push_back(radar_data);
                break;
            }
        }
    }
	
	if(is_separate)
	{
		pdw_vec_.clear();
		pdw_vec_.assign(pdw_list.begin(),pdw_list.end());
		return SUCCESSFUL;
	}
	return FAILED;
}


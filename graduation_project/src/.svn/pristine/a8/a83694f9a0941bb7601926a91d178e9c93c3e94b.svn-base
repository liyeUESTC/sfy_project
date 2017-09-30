
#include "cdif_algorithm.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "file_save_manager.h"

CDIFAlgorithm::CDIFAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
        double sample_time,double percent_param)
        :Algorithm(pdw_vec),sample_time_(sample_time),percent_param_(percent_param)
{
}

int CDIFAlgorithm::Run()
{        
    std::map<double,int> cumulative_difference_map;
    //cumulative difference histogram
    for(int level = 1;level < kCDIFMaxOrder;++level )
    {
        if(pdw_vec_.size()/level < 5)
        {
            std::cout << "data is little" << std::endl;
            return SUCCESSFUL;
        }
        for(int i = 0; i < pdw_vec_.size() - level;++i)
        {
        //    cumulative_difference_vec.push_back(pdw_vec_[i+level].toa - pdw_vec_[i].toa);
            double toa = pdw_vec_[i+level].toa - pdw_vec_[i].toa;
//            std::cout << toa << std::endl;
       
            if(cumulative_difference_map.size() == 0)
                cumulative_difference_map[toa] = 1;
            else
            {
                auto iter = cumulative_difference_map.begin();  
                for(;iter != cumulative_difference_map.end();++iter)
                {
                    if(toa > (iter->first)*kCDIFMinToleranceValue && toa < (iter->first)*kCDIFMaxToleranceValue)
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
        for(auto iter = cumulative_difference_map.begin();iter != cumulative_difference_map.end();++iter)
        {
            double threshold_value = sample_time_ / iter->first * percent_param_;
            std::cout << iter->first << "   "
                      << iter->second << "   "
                      << threshold_value << std::endl; 

            LineData line_data;
            line_data.push_back(iter->first);
            line_data.push_back(iter->second);
            line_data.push_back(threshold_value);
            file_data.push_back(line_data);

            if(iter->second > threshold_value)
            {
                for(auto iter1 = iter;iter1 != cumulative_difference_map.end();++iter1)
                {
                    double times= iter1->first / iter->first;
                    if( times > 2 * kCDIFMinToleranceValue && times < 2 * kCDIFMaxToleranceValue)
                    {
                        if(iter1->second > sample_time_/ iter1->first * percent_param_)
                        {
                            auto iter_pri = pri_vec.begin();
                            for(;iter_pri != pri_vec.end();++iter_pri)
                            {
                                if(iter->first > *iter_pri*kCDIFMinToleranceValue && iter->first < *iter_pri*kCDIFMaxToleranceValue)
                                    break;
                            }
                            if(iter_pri == pri_vec.end())
                                pri_vec.push_back(iter->first);
                        }
                    }
                }
            }
        }

        std::string file_name = "CDIF" + ToStr(level) +"阶差值直方图.ouput";
        FileSaveManager::GetInstance()->AddFile(file_name,file_data);
       // cumulative_difference_map.clear();
        if( pri_vec.size() != 0 && PDWDetection(pri_vec) == SUCCESSFUL)
        {
            level = 0;
            cumulative_difference_map.clear();
            std::cout << "剩余脉冲数：" << pdw_vec_.size() << std::endl;
        }
    }
    return SUCCESSFUL;
}

int CDIFAlgorithm::PDWDetection(const std::vector<double> &pri_vec)
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
                    if(iter2->toa - standard_pdw->toa < *iter_pri *kCDIFMinToleranceValue)
                        continue;
                    else if(iter2->toa - standard_pdw->toa >*iter_pri*kCDIFMaxToleranceValue)
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
                    if((times - times_int <= 0.5 && times <= times_int*kCDIFMaxToleranceValue) ||
                        (times-times_int > 0.5 && times >= (times_int+1)*kCDIFMinToleranceValue))
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

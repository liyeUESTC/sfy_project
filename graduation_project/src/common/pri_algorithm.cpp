#include "pri_algorithm.h"

#include <math.h>

#include <vector>
#include <map>
#include <list>
#include <iostream>

#include "file_save_manager.h"

PRIAlgorithm::PRIAlgorithm(const std::vector<struct PulseDescribeWord> &pdw_vec,
						double sample_time,double pri_param1,
						double pri_param2,double pri_param3)
						:Algorithm(pdw_vec),pri_param1_(pri_param1),
						sample_time_(sample_time),pri_param2_(pri_param2),
						pri_param3_(pri_param3)
						{}
						
int PRIAlgorithm::Run()
{
    std::vector<double> pri_vec = PriMeasure();
    PdwDetection(pri_vec);
    return SUCCESSFUL; 
}


std::vector<double> PRIAlgorithm::PriMeasure() const
{
	
	std::map<double,struct Pri> pri_map;
	for(int i = 0;i < kPRIIntervalNum;++i)
	{
		double middle = (i+0.5)*kPRIIntervalWidth + kPRIMinPriValue;
        struct PRIAlgorithm::Pri pri();
	    pri_map[middle] = pri;	
	}
	

	for(int i = 1;i < pdw_vec_.size();++i)
	{
		for(int j = i -1;j >= 0;--j)
		{
			double pri = pdw_vec_[i].toa - pdw_vec_[j].toa;
			if(pri > kPRIMaxPriValue)
				break;
			if(pri > kPRIMinPriValue && pri < kPRIMaxPriValue)
			{
				for(auto iter = pri_map.begin();iter != pri_map.end();++iter)
				{
					if(pri >= iter->first-kPRIIntervalWidth/2.0 &&
						pri < iter->first+kPRIIntervalWidth/2.0)
					{
						iter->second.data1 += cos(2.0*kMathConstantPi*pdw_vec_[i].toa
							/ pri);
					    iter->second.data2 += sin(2.0*kMathConstantPi*pdw_vec_[i].toa
							/pri);
                        iter->second.num++;
					}
				}
			}
		}
	}
	
	std::vector<double> pri_vec;
    std::cout << "PRI直方图" << std::endl;
    std::vector<LineData> file_data;
	for(auto iter = pri_map.begin();iter != pri_map.end();++iter)
	{
		double temp_pri_num = sqrt(pow(iter->second.data1,2) 
								+ pow(iter->second.data2,2));
		double threshold_value1 = pri_param1_ *  sample_time_ / iter->first;
        double threshold_value2 = pri_param2_ * iter->second.num;
        double threshold_value3 = pri_param3_ * sqrt(sample_time_ * pow(pdw_vec_.size()/sample_time_,2)* kPRIIntervalWidth);

        double threshold_value = MyMax(threshold_value1,MyMax(threshold_value2,threshold_value3));
        std::cout << iter->first << "   "
			      << temp_pri_num << "   "
			      << threshold_value << std::endl;
        //save file
        LineData line_data;
        line_data.push_back(iter->first);
        line_data.push_back(temp_pri_num);
        line_data.push_back(threshold_value);
        file_data.push_back(line_data);

		if(temp_pri_num > threshold_value)
		{
			pri_vec.push_back(iter->first);
            std::cout << "find" << std::endl;
		}
	}

    //save file
    FileSaveManager::GetInstance()->AddFile("PRI直方图.ouput",file_data);

	return pri_vec;
}

int PRIAlgorithm::PdwDetection(const std::vector<double> &pri_vec)
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
                    if(iter2->toa - standard_pdw->toa < *iter_pri *kPRIMinToleranceValue)
                        continue;
                    else if(iter2->toa - standard_pdw->toa >*iter_pri*kPRIMaxToleranceValue)
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
                    if((times - times_int <= 0.5 && times <= times_int*kPRIMaxToleranceValue) ||
                        (times-times_int > 0.5 && times >= (times_int+1)*kPRIMinToleranceValue))
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

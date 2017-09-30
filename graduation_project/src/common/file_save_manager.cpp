#include "file_save_manager.h"

#include <fstream>
#include <iostream>

#include "base_define.h"

int FileSaveManager::AddFile(const std::string &file_name,std::vector<LineData> &file_data)
{
	struct FileObject file_object;
	if(file_name.empty() || file_data.size() == 0)
		return FAILED;
	file_object.file_name = file_name;
	file_object.file_data = file_data;
	file_object_vec_.push_back(file_object);
	return SUCCESSFUL;
}

int FileSaveManager::SaveFile() const
{
	for(auto iter1 = file_object_vec_.begin();iter1 != file_object_vec_.end();++iter1)
	{
		std::ofstream ouput(iter1->file_name);
		if(!ouput.is_open())
		{
			std::cout << "open file error" << std::endl;
			return FAILED;
		}
		
		for(auto iter2 = iter1->file_data.begin();iter2 != iter1->file_data.end();
			++iter2)
		{
            int i = 1;
			for(auto iter3 = iter2->begin();iter3 != iter2->end();++iter3,++i)
			{
				ouput << *iter3;
                if(i % 3 != 0) 
                    ouput << "   ";
			}
			ouput << std::endl;
		}
		
		ouput.close();
	}
	return SUCCESSFUL;
}

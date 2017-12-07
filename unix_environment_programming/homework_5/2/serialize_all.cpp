/*************************************************************************
	> File Name: serialize_all.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 16时34分59秒
    > Function: 
 ************************************************************************/

#include "serialize_all.h"

#include <iostream>

bool SerializeAll::Serialize(const char *path,const std::vector<SerializeObjectA> &vec)
{
    FileOperation file_operation(path,O_RDWR|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
    for(int i = 0;i < vec.size();++i)
    {
        vec[i].Serialize(file_operation);
    }
    return true;
}

bool SerializeAll::Deserialize(const char *path,std::vector<SerializeObjectA> &vec)
{
    FileOperation file_operation(path,O_RDWR);
    while(1)
    {
        SerializeObjectA serialize_object_A;
        if(serialize_object_A.Deserialize(file_operation) == true)
            vec.push_back(serialize_object_A);
        else 
            break;
    }
    return true;
}



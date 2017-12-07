/*************************************************************************
	> File Name: main.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 15时34分41秒
    > Function: 
 ************************************************************************/
#include <vector>
#include <iostream>

#include "serialize_all.h"
#include "serialize_object_A.h"

int main(int argc,char *argv[])
{
    {
        SerializeObjectA a1(5),a2(7),a3(8);
        std::vector<SerializeObjectA> vec;
        vec.push_back(a1);
        vec.push_back(a2);
        vec.push_back(a3);
        SerializeAll serialize_all;
        serialize_all.Serialize("data",vec);
    }
    {
        SerializeAll serialize_all;
        std::vector<SerializeObjectA> vec;
        serialize_all.Deserialize("data",vec);
        std::cout << "vec_size:" << vec.size() << std::endl; 
        for(int i = 0;i < vec.size();++i)
        {
            vec[i].PrintParam();
        }
    }
    return 0;
}

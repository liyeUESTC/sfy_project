/*************************************************************************
	> File Name: serialize_all.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 16时30分04秒
    > Function: 
 ************************************************************************/

#ifndef SERIALIZE_ALL_H_
#define SERIALIZE_ALL_H_

#include <vector>

#include "serialize_object_A.h"

class SerializeAll
{
public:
    SerializeAll() {};
    bool Serialize(const char *path,const std::vector<SerializeObjectA> &vec);
    bool Deserialize(const char *path,std::vector<SerializeObjectA> &vec);
};
#endif

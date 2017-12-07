/*************************************************************************
	> File Name: serialize_object_A.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 15时13分44秒
    > Function: 
 ************************************************************************/

#ifndef SERIALIZE_OBJECT_A_H_
#define SERIALIZE_OBJECT_A_H_

#include "file_operation.h"

class SerializeObjectA
{
public:
    SerializeObjectA();
    SerializeObjectA(int i);
    void PrintParam();
    bool Serialize(FileOperation &file_operation) const;
    bool Deserialize(FileOperation &file_operation);
private:
    int i_;
};
#endif

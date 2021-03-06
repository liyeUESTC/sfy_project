/*************************************************************************
	> File Name: serialize_object_A.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 15时21分56秒
    > Function: 
 ************************************************************************/

#include "serialize_object_A.h"

#include <iostream>

#include "return_status.h"
#include "file_operation.h"

SerializeObjectA::SerializeObjectA()
{
    i_ = 0;
}

SerializeObjectA::SerializeObjectA(int i)
{
    i_ = i;
}

void SerializeObjectA::PrintParam()
{
    std::cout << "in PrintParam:" << i_ << std::endl;
}

bool SerializeObjectA::Serialize(FileOperation &file_operation) const 
{
    ReturnStatus return_status = file_operation.Write(&i_,sizeof(i_));
    if(return_status.return_value() == -1)
        return false;
    return true;
}

bool SerializeObjectA::Deserialize(FileOperation &file_operation)
{
    ReturnStatus return_status = file_operation.Read(&i_,sizeof(i_));
    if(return_status.return_value() == -1)
        return false;
    return true;
}

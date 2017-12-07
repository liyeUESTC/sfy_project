/*************************************************************************
	> File Name: main.cpp
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 15时34分41秒
    > Function: 
 ************************************************************************/

#include "serialize_object_A.h"

int main(int argc,char *argv[])
{
    {
        SerializeObjectA serialize_object_A(13);
        serialize_object_A.Serialize("data");
    }
    {
        SerializeObjectA serialize_object_A;
        serialize_object_A.DeSerialize("data");
        serialize_object_A.PrintParam();
    }
    return 0;
}

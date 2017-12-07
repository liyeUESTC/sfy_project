/*************************************************************************
	> File Name: serialize_object_A.h
	> Author: sfy
	> Mail: 
	> Created Time: 2017年12月07日 星期四 15时13分44秒
    > Function: 
 ************************************************************************/

#ifndef SERIALIZE_OBJECT_A_H_
#define SERIALIZE_OBJECT_A_H_


class SerializeObjectA
{
public:
    SerializeObjectA();
    SerializeObjectA(int i);
    void PrintParam();
    bool Serialize(const char *path);
    bool DeSerialize(const char *path);
private:
    int i_;
};
#endif

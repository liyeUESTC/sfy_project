/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Oct 2017 03:22:16 PM CST
 ************************************************************************/
#include "my_dictionary.h"
#include<iostream>
#include<string>

using namespace std;

int main()
{
    MyDictionary<int,string> my_dictionary;
    my_dictionary.Insert(MyPair<int,string> (2,"123"));
    std::cout << my_dictionary.Empty() << std::endl
              << my_dictionary.Size() << std::endl;

    std::cout << "before erase::";
    auto ptr = my_dictionary.Find(2);
    if(ptr == nullptr)
    {
        std::cout << " not find the key" << std::endl;
    }
    else
        std::cout << "find the key" << std::endl;

    my_dictionary.Erase(2);
    ptr = my_dictionary.Find(2);
    std::cout << "after erase::";
    if(ptr == nullptr)
        std::cout << "not find the key" << std::endl;
    else
        std::cout << "find the key" << std::endl;
    return 0;
}




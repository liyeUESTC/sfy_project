#include <iostream>
#include "my_stack.h"
  
int main(int argc,char *argv[])
{
    MyStack<int> stack(10); 
    for(int i = 0;i <11;++i)
        stack.push(i);
    std::cout << stack.size() << std::endl
              << stack.top() << std::endl;  
    stack.pop();
    std::cout << stack.size() << std::endl
              << stack.top() << std::endl; 
}

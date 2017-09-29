#include <iostream>
#include "my_queue.h"

int main(int argc,char *argv[])
{
    MyQueue<int> my_queue;   
    for(int i = 0;i < 10;++i)
       my_queue.push(i);
    std::cout << my_queue.size() << std::endl
              << my_queue.back() << std::endl; 

   for(int i = 0;i < 4;++i)
      my_queue.pop();

   for(int i = 0;i < 3;++i)
      my_queue.push(i);

   std::cout << my_queue.size() << std::endl
             << my_queue.front() << std::endl
             << my_queue.back() << std::endl; 
}

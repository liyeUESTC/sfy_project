#include "linked_list.h"

#include <iostream>

int main(int argc, char *argv[])
{
	LinkedList<int> linked_list;
	for (int i = 0; i < 10; ++i)
	{
		linked_list.PushBack(i);
	}

	for (int i = 0; i < linked_list.Size(); ++i)
		std::cout << linked_list.Get(i) << "   ";

	std::cout << std::endl;
	/*linked_list.RemoveRange(0,10);
	std::cout << linked_list.Size() << std::endl;*/
	//for (int i = 0; i < linked_list.Size(); ++i)
		//std::cout << linked_list.Get(i) << "   ";

	char a;
	std::cin >> a;
	return 0;
}
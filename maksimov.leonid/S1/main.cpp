#include <iostream>
#include <string>
#include "list.hpp"

int main()
{
	//std::string str = "";
	//char temp = 0;
	//std::cin >> std::noskipws;
	//while (!std::cin.eof())
	//{
	//	std::cin >> temp;
	//	if (temp == '\n')
	//	{
	//		std::cout << str << "\n";
	//		str = "";
	//	}
	//	str += temp;
	//}
	//std::cin >> std::skipws;
	maksimov::List< int > lst;
	lst.pushBack(1);
	lst.pushBack(2);
	return 0;
}

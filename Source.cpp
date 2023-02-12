#include <iostream>
#include <string>
#include "Bitset.h"

int main()
{
	//case1
	bitset<20> bset1;
	bset1.set(1);
	std::string str1 = bset1.to_string();
	std::cout << str1 << std::endl;
	bset1.reset(1);
	str1 = bset1.to_string();
	std::cout << str1 << std::endl;
	std::cout << "None: " << std::boolalpha << bset1.none() << std::endl;
	for (int i = 1; i < 21; i++)
		bset1.set(i);
	str1 = bset1.to_string();
	std::cout << str1 << std::endl;
	std::cout << "All: " << std::boolalpha << bset1.all() << std::endl;

	//case2
	bitset<45> bset2;
	bset2.set(34);
	bset2.set(45);
	bset2.set(1);
	std::string str2 = bset2.to_string();
	std::cout << str2 << std::endl;
	bset2.reset(1);
	bset2.reset(34);
	std::string str3 = bset2.to_string();
	std::cout << str3 << std::endl;
	bset2.flip(34);
	bset2.flip(1);
	std::string str4 = bset2.to_string();
	std::cout << str4 << std::endl;
	std::cout << "Size:\t" << bset2.Size() << '\n' << "Count:\t" << bset2.count() << '\n' << "Bset[34]:\t" << bset2[34] << std::endl;


}
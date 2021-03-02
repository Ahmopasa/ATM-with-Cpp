#include "ATM.h"

/*
#include<iostream>

std::unique_ptr<int> ChangeValue(std::unique_ptr<int> temp_ptr)
{

	*temp_ptr += 100;

	return temp_ptr;
}

void ui(void)
{
	int x = 0;
	std::unique_ptr<int> x_ptr = std::make_unique<int>(x);
	std::cout << "Address : " << x_ptr << std::endl;
	std::cout << "Value   : " << *x_ptr << std::endl;

	std::unique_ptr<int> x_ptr_2 = ChangeValue(std::move(x_ptr));
	std::cout << "Address : " << x_ptr_2 << std::endl;
	std::cout << "Value   : " << *x_ptr_2 << std::endl;

	std::unique_ptr<int> x_ptr_3 = ChangeValue(std::move(x_ptr_2));
	std::cout << "Address : " << x_ptr_3 << std::endl;
	std::cout << "Value   : " << *x_ptr_3 << std::endl;
}
*/


int main()
{
	while (true)
	{
		UserScreen();
	}





	
	return 0;
}
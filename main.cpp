#include "ATM.h"

// Usage of Smart Pointers
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

// Usage of Overloaded Templates
/* 
#include<iostream>

void static IgnoreBuffer(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void ReadWithCin(T& variable)
{
	while (true)
	{
		std::cout << "Enter a input : ";
		std::cin >> variable;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail() || variable < -1)
		{
			std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n"; continue;
		}
		else
		{
			switch (variable)
			{
				case -1:
				{
					std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
				}
				case 1:
				{
					std::cout << "Case 1 was chosen.\n"; break;
				}
				case 2:
				{
					std::cout << "Case 2 was chosen.\n"; break;
				}
				case 3:
				{
					std::cout << "Case 3 was chosen.\n"; break;
				}
				case 4:
				{
					std::cout << "Case 4 was chosen.\n"; break;
				}
				default:
				{
					std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n"; continue;
				}
			}
			break;
		}
	}
}

template <typename T>
void ReadWithCinString(T& variable)
{

	std::cout << "Passed string : " << variable << std::endl;

}

int main()
{

//	while (true)
//	{
//		UserScreen();
//	}



std::cout << "\nWhat would you like to do?\n";
std::cout << "To See Account Information : 1\n";
std::cout << "To Deposit Cash            : 2\n";
std::cout << "To Withdraw Cash           : 3\n";
std::cout << "To Change Account Info.    : 4\n";
std::cout << "To Exit                    : -1\n";
short customerChoice{};
ReadWithCin(customerChoice);
ReadWithCinString("John Johny");



return 0;
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
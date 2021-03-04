#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

#include "ATM_Program.h"

void static IgnoreBuffer(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

template <typename T>
void ReadWithCinNumeric(T& variable)
{
	while (true)
	{
		std::cout << "Input: ";
		std::cin >> variable;
		std::cin.clear();
		IgnoreBuffer();
		if (std::cin.fail() || variable < 1)
		{
			continue;
		}
		break;
	}
}

template <typename T>
void ReadWithCinChar(T& variable)
{
	while (true)
	{
		std::cout << "Input: ";
		std::cin >> variable;
		std::cin.clear();
		IgnoreBuffer();
		if (std::cin.fail() || variable < 1)
		{
			continue;
		}
		break;
	}
}

template <typename T>
void ReadWithString(T& variable)
{
	while (true)
	{
		std::cout << "Input: ";
		std::cin >> variable;
		std::cin.clear();
		IgnoreBuffer();
		bool statusString = std::find_if(variable.begin(), variable.end(), [](char c) { return !std::isalpha(c); }) != variable.end();

		if (!std::cin.fail() && !statusString)
		{
			break;
		}
		else
		{
			continue;
		}
	}
}

std::unique_ptr<AccountOwner> CreateAccount(const int& PinCode)
{
	system("cls");
	std::cout << "How would you like to create an account for the customer?\n";
	std::cout << "With specific values   :  2\n";
	std::cout << "To Exit                :  1\n";

	while (true)
	{
		int choice{};
		ReadWithCinNumeric(choice);
		switch (choice)
		{
			case 2:
			{
				system("cls");
				std::cout << "Please, specify these values;\n";
				std::string customerName;
				std::string customerSurame;
				std::string customerAddress;
				unsigned int customerAccountBalance;
				unsigned int customerAccountPINCode = PinCode;

				std::cout << "Name:       "; ReadWithString(customerName);
				std::cout << "Surname:    "; ReadWithString(customerSurame);
				std::cout << "Address:    "; ReadWithString(customerAddress);
				std::cout << "Balance:    "; ReadWithCinNumeric(customerAccountBalance);

				bool customerAccountVipStatus = (customerAccountBalance >= 1'000'000) ? true : false;

				std::unique_ptr<AccountOwner> customer_ptr = std::make_unique<AccountOwner>(customerName, customerSurame, customerAddress, customerAccountBalance, customerAccountPINCode, customerAccountVipStatus);

				return SaveAccountInfo(std::move(customer_ptr));
			}
			case 1:
			{
				system("cls"); std::cout << "No account were created. Program is exiting by request."; exit(EXIT_SUCCESS);
			}
			default:
			{
				continue;
			}
		}
	}
}

std::unique_ptr<AccountOwner> ReadAccountInfo(const int& PinCode)
{

	std::ifstream FileHandler{};
	FileHandler.open(std::to_string(PinCode));
	if (FileHandler.good())
	{
		std::string tempString;
		std::vector<std::string> tempStringVector;
		while (FileHandler.good())
		{
			std::getline(FileHandler, tempString);
			tempStringVector.push_back(tempString);
		}
		FileHandler.close();

		std::unique_ptr<AccountOwner> customer = std::make_unique<AccountOwner>();
		customer->setName(tempStringVector[0]);
		customer->setSurname(tempStringVector[1]);
		customer->setAddress(tempStringVector[2]);
		customer->setBalance(std::stoi(tempStringVector[3]));
		customer->setAccountPINCode(PinCode);
		customer->setAccountVipStatus(std::stoi(tempStringVector[4]));

		return customer;
	}
	else
	{
		std::cout << "Such _" << PinCode << "_ Pin Code could not be found. Please make sure that you have entered a valid pin code.\n";
		std::cout << "Would you like to create a new one? [Y/N]\n";
		while (true)
		{
			char choice{ 0 };
			ReadWithCinChar(choice);
			switch (choice)
			{
				case 'y':
				case 'Y':
				{
					[[__fallthrough]]; return CreateAccount(PinCode);
				}
				case 'n':
				case 'N':
				{
					[[__fallthrough]]; system("cls"); std::cout << "No account were created. Program is exiting by request."; exit(EXIT_SUCCESS);
				}
				default:
				{
					continue;
				}
			}
		}
	}
}

void UserScreen(void)
{

	std::cout << "Welcome to the ATM Machine. Please, enter your name and PIN code to proceed.\n";
	std::cout << "< If you do not have any PIN code, or it is not reachable, please press 9999. >\n";

	while (true)
	{
		short PinCode{};
		ReadWithCinNumeric(PinCode);

		while (true)
		{
			system("cls");
			std::unique_ptr<AccountOwner> customer = ReadAccountInfo(PinCode);
			std::cout << "Welcome => " << customer->getName() << "!\n";
			std::cout << "\nWhat would you like to do?\n";
			std::cout << "To Change Account Info.    : 5\n";
			std::cout << "To Withdraw Cash           : 4\n";
			std::cout << "To Deposit Cash            : 3\n";
			std::cout << "To See Account Information : 2\n";
			std::cout << "To Exit                    : 1\n";
			short customerChoice{};
			ReadWithCinNumeric(customerChoice);
			switch (customerChoice)
			{
				case 5:
				{
					ChangeAccountInfo(PinCode); break;
				}
				case 4:
				{
					WithdrawCurrency(std::move(customer)); break;
				}
				case 3:
				{
					DepositCurrency(std::move(customer)); break;
				}
				case 2:
				{
					CheckAccountInfo(std::move(customer)); break;
				}
				case 1:
				{
					std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
				}
				default:
				{
					continue;
				}
			}
		}
		break;
	}
}

void CheckAccountInfo(std::unique_ptr<AccountOwner> customer)
{
	system("cls");
	std::cout << "=============================================" << std::endl;
	std::cout << "Information of customer    :\n";
	std::cout << "Name                       : " << customer->getName() << std::endl;
	std::cout << "Surname                    : " << customer->getSurname() << std::endl;
	std::cout << "Address                    : " << customer->getAddress() << std::endl;
	std::cout << "AccountBalance             : " << customer->getBalance() << std::endl;
	std::cout << "AccountPINCode             : " << customer->getAccountPINCode() << std::endl;
	std::cout << "AccountVipStatus           : " << std::boolalpha << customer->getAccountVipStatus() << std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << "Would you like to continue[y], or exit[n]? : ";
	while (true)
	{
		char choice;
		ReadWithCinChar(choice);

		switch (choice)
		{
			case 'y':
			case 'Y':
			{
				[[__fallthrough]]; system("cls"); break;
			}
			case 'n':
			case 'N':
			{
				[[__fallthrough]]; std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
			}
			default:
			{
				continue;
			}
		}
		break;
	}
}

void DepositCurrency(std::unique_ptr<AccountOwner> customer)
{
	while (true)
	{
		system("cls");
		std::cout << "How much TL will you deposit to? : " << std::flush;
		int depositAmount{};
		ReadWithCinNumeric(depositAmount);

		customer->setBalance(customer->getBalance() + depositAmount);
		std::cout << "Currently, customer have " << customer->getBalance() << "TL in his/her bank account.\n";
		break;
	}

	if (customer->getBalance() > 1'000'000)
	{
		customer->setAccountVipStatus(true);
	}

	SaveAccountInfo(std::move(customer));

	while (true)
	{
		std::cout << "Would you like to continue[y], or exit[n]? : ";
		char choice;
		ReadWithCinChar(choice);

		switch (choice)
		{
			case 'y':
			case 'Y':
			{
				[[__fallthrough]]; system("cls"); break;
			}
			case 'n':
			case 'N':
			{
				[[__fallthrough]]; std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
			}
			default:
			{
				continue;
			}
		}
		break;
	}
}

void WithdrawCurrency(std::unique_ptr<AccountOwner> customer)
{
	while (true)
	{
		system("cls");
		std::cout << "How much TL will you withdraw from? : " << std::flush;
		int withdrawAmount{};
		ReadWithCinNumeric(withdrawAmount);

		if (customer->getBalance() >= static_cast<unsigned int>(withdrawAmount))
		{
			customer->setBalance(customer->getBalance() - withdrawAmount);
			std::cout << "Currently, customer have " << customer->getBalance() << "TL in his/her bank account.\n";
			break;
		}
		else
		{
			std::cout << "You do not have that much of cash money either in your account or in ATM.\n";
			std::cout << "Cash in Your Account      : " << customer->getBalance() << "\n";
			std::cout << "Cash you wish to withdraw : " << withdrawAmount << "\n";
			std::cout << "Enter Cash Amount Again   : ";
			continue;
		}
	}

	if (customer->getBalance() <= 1'000'000)
	{
		customer->setAccountVipStatus(false);
	}

	SaveAccountInfo(std::move(customer));

	while (true)
	{
		std::cout << "Would you like to continue[y], or exit[n]? : ";
		char choice;
		ReadWithCinChar(choice);

		switch (choice)
		{
			case 'y':
			case 'Y':
			{
				[[__fallthrough]]; system("cls"); break;
			}
			case 'n':
			case 'N':
			{
				[[__fallthrough]]; std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
			}
			default:
			{
				continue;
			}
		}
		break;
	}
}

int ChangeAccountInfo(const int& PinCode)
{
	while (true)
	{
		system("cls");
		std::unique_ptr<AccountOwner> customer = ReadAccountInfo(PinCode);
		std::cout << "Which piece of information would you like to change?\n";
		std::cout << "To Go to Main Menu: 6\n";
		std::cout << "To Change PIN Code: 5\n";
		std::cout << "To Change Address : 4\n";
		std::cout << "To Change Surname : 3\n";
		std::cout << "To Change Name    : 2\n";
		std::cout << "To Exit           : 1\n";
		int choice{};
		ReadWithCinNumeric(choice);

		switch (choice)
		{
		case 6:
		{
			return 1;
		}
		case 5:
		{
			int temp_PinCode;
			std::string OldPinCode = std::to_string(customer->getAccountPINCode());
			std::remove(OldPinCode.c_str());

			std::cout << "Enter the new Pin Code for customer:";
			ReadWithCinNumeric(temp_PinCode);

			customer->setAccountPINCode(temp_PinCode);
			std::cout << "Your PIN Code has been changed. Your new PIN Code is : " << customer->getAccountPINCode() << std::endl;
			SaveAccountInfo(std::move(customer));

			std::cout << "Would you like to change another information, or come back to main menu?\n";
			std::cout << "(Y/y) : To change another information,\n";
			std::cout << "(N/n) : To come back to main menu,\n";

			while (true)
			{
				char choice;
				ReadWithCinChar(choice);
				switch (choice)
				{
					case 'y':
					case 'Y':
					{
						[[__fallthrough]]; system("cls"); break;
					}
					case 'n':
					case 'N':
					{
						[[__fallthrough]]; system("cls"); return 1;
					}
					default:
					{
						std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
					}
				}
				break;
			}
			continue;
		}
		case 4:
		{
			std::string Address;
			std::cout << "Enter the new address for customer.\n";
			ReadWithString(Address);

			customer->setAddress(Address);
			std::cout << "Your address has been changed. Your new address is : " << customer->getAddress() << std::endl;
			SaveAccountInfo(std::move(customer));

			std::cout << "Would you like to change another information, or come back to main menu?\n";
			std::cout << "(Y/y) : To change another information,\n";
			std::cout << "(N/n) : To come back to main menu,\n";

			while (true)
			{
				char choice;
				ReadWithCinChar(choice);
				switch (choice)
				{
					case 'y':
					case 'Y':
					{
						[[__fallthrough]]; system("cls"); break;
					}
					case 'n':
					case 'N':
					{
						[[__fallthrough]]; system("cls"); return 1;
					}
					default:
					{
						std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
					}
				}
				break;
			}
			continue;
		}
		case 3:
		{
			std::string Surname;
			std::cout << "Enter the new surname for customer.\n";
			ReadWithString(Surname);

			customer->setSurname(Surname);
			std::cout << "Your surname has been changed. Your new surname is : " << customer->getSurname() << std::endl;
			SaveAccountInfo(std::move(customer));

			std::cout << "Would you like to change another information, or come back to main menu?\n";
			std::cout << "(Y/y) : To change another information,\n";
			std::cout << "(N/n) : To come back to main menu,\n";

			while (true)
			{
				char choice;
				ReadWithCinChar(choice);
				switch (choice)
				{
					case 'y':
					case 'Y':
					{
						[[__fallthrough]]; system("cls"); break;
					}
					case 'n':
					case 'N':
					{
						[[__fallthrough]]; system("cls"); return 1;
					}
					default:
					{
						std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
					}
				}
				break;
			}
			continue;
		}
		case 2:
		{
			std::string Name;
			std::cout << "Enter the new name for customer.\n";
			ReadWithString(Name);

			customer->setName(Name);
			std::cout << "Your name has been changed. Your new name is : " << customer->getName() << std::endl;
			SaveAccountInfo(std::move(customer));

			std::cout << "Would you like to change another information, or come back to main menu?\n";
			std::cout << "(Y/y) : To change another information,\n";
			std::cout << "(N/n) : To come back to main menu,\n";

			while (true)
			{
				char choice;
				ReadWithCinChar(choice);
				switch (choice)
				{
					case 'y':
					case 'Y':
					{
						[[__fallthrough]]; system("cls"); break;
					}
					case 'n':
					case 'N':
					{
						[[__fallthrough]]; system("cls"); return 1;
					}
					default:
					{
						std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
					}
				}
				break;
			}
			continue;
		}
		case 1:
		{
			std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
		}
		default:
		{
			continue;
		}
		}
	}
}


std::unique_ptr<AccountOwner> SaveAccountInfo(std::unique_ptr<AccountOwner> customer)
{
	std::ofstream fileHandler;
	if (!fileHandler)
	{
		std::cout << "Failed to open _" << std::to_string(customer->getAccountPINCode()) << "_. Exiting from the program.\n";
		exit(EXIT_FAILURE);
	}

	fileHandler.open(std::to_string(customer->getAccountPINCode()));
	fileHandler << customer->getName() << "\n" << customer->getSurname() << "\n" << customer->getAddress() << "\n" << customer->getBalance() << "\n" << customer->getAccountVipStatus() << "\n";

	fileHandler.close();

	return customer;
}
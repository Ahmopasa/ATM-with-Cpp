#include "ATM.h"

int AccountOwner::AccountTransactionCounter{0};

const std::string& AccountOwner::getName() const
{
	return Name;
}

void AccountOwner::setName(const std::string& tempName)
{
	Name = tempName;
}

const std::string& AccountOwner::getSurname() const
{
	return Surname;
}

void AccountOwner::setSurname(const std::string& tempSurname)
{
	Surname = tempSurname;
}

const std::string& AccountOwner::getAddress() const
{
	return Address;
}

void AccountOwner::setAddress(const std::string& tempAddress)
{
	Address = tempAddress;
}

const int& AccountOwner::getBalance() const
{
	return AccountBalance;
}

void AccountOwner::setBalance(const int& tempBalance)
{
	AccountBalance = tempBalance;
}

const int& AccountOwner::getAccountPINCode() const
{
	return AccountPINCode;
}

void AccountOwner::setAccountPINCode(const int& tempPINCode)
{
	AccountPINCode = tempPINCode;
}

const bool& AccountOwner::getAccountVipStatus() const
{
	return AccountVipStatus;
}

void AccountOwner::setAccountVipStatus(const bool& tempVipStatus)
{
	AccountVipStatus = tempVipStatus;
}

AccountOwner::AccountOwner(void)
{
	Name = "NoName";
	Surname = "NoSurname";
	Address = "NoAddress";

	AccountBalance = 0;
	AccountPINCode = 0;

	AccountVipStatus = AccountBalance > 1'000'000 ? true : false;

	//std::cout << ++AccountTransactionCounter << " - " << "Constructor for AccountOwner, with predetermined values, was called." << std::endl;

}

AccountOwner::AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, int& tempBalance, int& tempPINCode, bool tempVipStatus) : Name{ tempName }, Surname{ tempSurname }, Address{ tempAddress }, AccountBalance{ tempBalance }, AccountPINCode{ tempPINCode }, AccountVipStatus{ tempVipStatus }
{
	//std::cout << ++AccountTransactionCounter << " - " << "Constructor for AccountOwner, with desired values, was called." << std::endl;
}

AccountOwner::AccountOwner(const AccountOwner& tempObj)
{

	Name = tempObj.Name;
	Surname = tempObj.Surname;
	Address = tempObj.Address;

	AccountBalance = tempObj.AccountBalance;
	AccountPINCode = tempObj.AccountPINCode;

	AccountVipStatus = tempObj.AccountVipStatus;

	//std::cout << ++AccountTransactionCounter << " - " << " Copy Constructor for AccountOwner was called." << std::endl;
}

AccountOwner::~AccountOwner()
{
	//std::cout << AccountTransactionCounter-- << "th Deconstruction was called" << std::endl;
}

void CheckAccountInfo(const std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "Information of customer - " << (i) << " :\n";
		std::cout << "Name: " << customerList[i].getName() << std::endl;
		std::cout << "Surname: " << customerList[i].getSurname() << std::endl;
		std::cout << "Address: " << customerList[i].getAddress() << std::endl;
		std::cout << "AccountBalance: " << customerList[i].getBalance() << std::endl;
		std::cout << "AccountPINCode: " << customerList[i].getAccountPINCode() << std::endl;
		std::cout << "AccountVipStatus: " << std::boolalpha << customerList[i].getAccountVipStatus() << std::endl;

	}
}

void DepositCurrency(std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "How much TL will you deposit to customer " << i + 1 << ": "<< std::flush;
		int depositAmount{};
		std::cin >> depositAmount;

		customerList[i].setBalance(customerList[i].getBalance() + depositAmount);

		std::cout << "Currently, customer- " << i << "have " << customerList[i].getBalance() << "TL in his/her bank account.\n";
	}
}

void WithdrawCurrency(std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "How much TL will you withdraw from customer " << i + 1 << ": " << std::flush;
		int withdrawAccount{};
		std::cin >> withdrawAccount;

		customerList[i].setBalance(customerList[i].getBalance() - withdrawAccount);

		std::cout << "Currently, customer- " << i << "have " << customerList[i].getBalance() << "TL in his/her bank account.\n";
	}
}

std::vector<AccountOwner>& CreateAccount(std::vector<AccountOwner>& customerList)
{
	unsigned int amount{};
	std::cout << "How many accounts will be created ? : ";
	std::cin >> amount;
	if (std::cin.fail())
	{
		std::cout << "Please, enter a numeric number!. Program is exiting."; exit(EXIT_FAILURE);
	}

	for (unsigned int counterList{}; counterList < amount; counterList++)
	{
		std::cout << "How would you like to create an account for the customer - " << counterList + 1 << "?\n";
		std::cout << "1. With predefined values.\n";
		std::cout << "2. With specific values.\n";
		std::cout << "0. To Exit.\n";
		std::cout << "Choice: ";

		unsigned int choice{};
		std::cin >> choice;
		if (std::cin.fail())
		{
			std::cout << "Please, enter a numeric number between 0 and 2!. Program is exiting."; exit(EXIT_FAILURE);
		}
		switch (choice)
		{
			case 1:
			{
				std::cout << "An account with predefined values has been created.\n";
				AccountOwner customer;
				customerList.push_back(customer);
				break;
			}
			case 2:
			{
				std::cout << "An account with specific values will be created. Please, specify these values;\n";
				std::string customerName;
				std::string customerSurame;
				std::string customerAddress;
				int customerAccountBalance;
				int customerAccountPINCode;
				bool customerAccountVipStatus;

				std::cout << "Please, Enter " << counterList << "th Customer's Information:\n";
				std::cout << "Name:       "; std::cin >> customerName;
				std::cout << "Surname:    "; std::cin >> customerSurame;
				std::cout << "Address:    "; std::cin >> customerAddress;
				std::cout << "Balance:    "; std::cin >> customerAccountBalance;
				std::cout << "PIN Code:   "; std::cin >> customerAccountPINCode;
				std::cout << "VIP Status: "; std::cin >> customerAccountVipStatus;

				AccountOwner customer{ customerName , customerSurame , customerAddress , customerAccountBalance , customerAccountPINCode , customerAccountVipStatus };

				customerList.push_back(customer);
				break;
			}
			case 0:
			{
				std::cout << "No account were created. Program is exiting."; exit(EXIT_FAILURE);
			}
			default:
			{
				std::cout << "Please, enter a number mentioned above. Program is exiting."; exit(EXIT_FAILURE);
			}
		}
	}
	return customerList;
}

void ChangeAccountInfo(std::vector<AccountOwner>& customerList)
{
	std::cout << "Which piece of information would you like to change?\n";
	std::cout << "To Exit:            0\n";
	std::cout << "To Change Name:     1\n";
	std::cout << "To Change Surname:  2\n";
	std::cout << "To Change Address:  3\n";
	std::cout << "To Change PIN Code: 4\n";
	std::cout << "Choice: ";

	unsigned int choice{};
	std::cin >> choice;

	for (size_t i = 0; i < customerList.size(); i++)
	{
		switch (choice)
		{
			case 0:
			{
				std::cout << "Exiting from the program.\n"; break;
			}
			case 1:
			{
				for (size_t i = 0; i < customerList.size(); i++)
				{
					std::string Name;
					std::cout << "Enter the new name for customer -" << i +1 << ": ";
					std::cin >> Name;

					customerList[i].setName(Name);
				}

				break;
			}
			case 2:
			{
				for (size_t i = 0; i < customerList.size(); i++)
				{
					std::string Surname;
					std::cout << "Enter the new surname for customer -" << i + 1 << ": ";
					std::cin >> Surname;

					customerList[i].setSurname(Surname);
				}

				break;
			}
			case 3:
			{
				for (size_t i = 0; i < customerList.size(); i++)
				{
					std::string Address;
					std::cout << "Enter the new address for customer -" << i + 1 << ": ";
					std::cin >> Address;

					customerList[i].setAddress(Address);
				}

				break;
			}
			case 4:
			{
				for (size_t i = 0; i < customerList.size(); i++)
				{
					int PinCode;
					std::cout << "Enter the new PIN Code for customer -" << i + 1 << ": ";
					std::cin >> PinCode;

					customerList[i].setAccountPINCode(PinCode);
				}

				break;
			}
		}
	}

}

void SaveAccountInfo(const std::vector<AccountOwner>& customerList)
{
	unsigned int customerAmount = customerList.size();
	std::ofstream* fileHandler = new std::ofstream[customerAmount];

		for (size_t i = 0; i < customerAmount; i++)
		{
			if (!fileHandler)
			{
				std::cout << "Failed to open _" << std::to_string(customerList[i].getAccountPINCode()) << "_. Exiting from the program.\n"; 
				exit(EXIT_FAILURE);
			}

			fileHandler[i].open(std::to_string(customerList[i].getAccountPINCode()));
			fileHandler[i] << customerList[i].getName() << "\n" << customerList[i].getSurname() << "\n" << customerList[i].getAddress() << "\n" << customerList[i].getBalance() << "\n" << customerList[i].getAccountVipStatus() << "\n";
			
			fileHandler[i].close();
		}

	delete[] fileHandler;
}

void UserScreen()
{
	std::vector<AccountOwner> customerList;

	std::cout << "Welcome to the ATM Machine. Please, enter your name and PIN code to proceed.\n";
	std::cout << "If you do not have any PIN code, or it is not reachable, please press 999.\n";
	std::cout << "PinCode : ";
	short PinCode{};
	std::cin >> PinCode;

	while (true)
	{
		if (std::cin.fail())
		{
			std::cout << "Please enter a numeric value.\n"; break;
		}
		else if (PinCode == 999)
		{
			std::cout << "What is your name, surname and address?\n"; break;
		}
		else if (PinCode < 0)
		{
			std::cout << "You entered below zero. Enter Again: "; std::cin >> PinCode;
		}
		else
		{
			ReadAccountInfo(PinCode, customerList);
			CheckAccountInfo(customerList);
			break;
		}
	}
}

std::vector<AccountOwner>& ReadAccountInfo(const int PinCode, std::vector<AccountOwner>& customerList)
{
		std::ifstream FileHandler;
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

			AccountOwner customer;
			customer.setName(tempStringVector[0]);
			customer.setSurname(tempStringVector[1]);
			customer.setAddress(tempStringVector[2]);
			customer.setBalance(std::stoi(tempStringVector[3]));
			customer.setAccountPINCode(PinCode);
			customer.setAccountVipStatus(std::stoi(tempStringVector[4]));

			customerList.push_back(customer);
		}
		else
		{
			std::cout << "Such _" << PinCode << "_ Pin Code could not be found. Please make sure that you have entered a valid pin code.\n";
		}
	return customerList;
}


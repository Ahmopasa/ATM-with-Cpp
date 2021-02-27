#include "ATM.h"
#include <limits>

ATM::ATM()
{
	ATMBalanceAmount = 1'000'000;
}

ATM::~ATM()
{
}

const unsigned int& ATM::getATMBalanceAmount(void) const
{
	return ATMBalanceAmount;
}

void ATM::setATMBalanceAmount(const unsigned int& tempBalance)
{
	ATMBalanceAmount = tempBalance;
}

int AccountOwner::AccountTransactionCounter{0};

void static IgnoreBuffer(void)
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

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

const unsigned int& AccountOwner::getBalance() const
{
	return AccountBalance;
}

void AccountOwner::setBalance(const unsigned int& tempBalance)
{
	AccountBalance = tempBalance;
}

const unsigned int& AccountOwner::getAccountPINCode() const
{
	return AccountPINCode;
}

void AccountOwner::setAccountPINCode(const unsigned int& tempPINCode)
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
}

AccountOwner::AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, unsigned int& tempBalance, unsigned int& tempPINCode, bool tempVipStatus) : Name{ tempName }, Surname{ tempSurname }, Address{ tempAddress }, AccountBalance{ tempBalance }, AccountPINCode{ tempPINCode }, AccountVipStatus{ tempVipStatus }
{
}

AccountOwner::AccountOwner(const AccountOwner& tempObj)
{
	Name = tempObj.Name;
	Surname = tempObj.Surname;
	Address = tempObj.Address;

	AccountBalance = tempObj.AccountBalance;
	AccountPINCode = tempObj.AccountPINCode;

	AccountVipStatus = tempObj.AccountVipStatus;
}

AccountOwner::~AccountOwner()
{
}

void CheckAccountInfo(const std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "Information of customer - " << (i) << " :\n";
		std::cout << "Name                       : " << customerList[i].getName() << std::endl;
		std::cout << "Surname                    : " << customerList[i].getSurname() << std::endl;
		std::cout << "Address                    : " << customerList[i].getAddress() << std::endl;
		std::cout << "AccountBalance             : " << customerList[i].getBalance() << std::endl;
		std::cout << "AccountPINCode             : " << customerList[i].getAccountPINCode() << std::endl;
		std::cout << "AccountVipStatus           : " << std::boolalpha << customerList[i].getAccountVipStatus() << std::endl;
		std::cout << "Total Amount of Transaction: " << customerList[i].AccountTransactionCounter << std::endl;
	}
}

void DepositCurrency(std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "How much TL will you deposit to customer " << i + 1 << ": "<< std::flush;
		
		while (true)
		{
			int depositAmount{};
			std::cin >> depositAmount;
			std::cin.clear();
			IgnoreBuffer();

			if (std::cin.fail())
			{
				std::cout << "You have entered an invalid cash amount. Please, make sure that you have entered a numeric value : ";
			}
			else if (depositAmount <= 0)
			{
				std::cout << "You have entered a valid input, but it was equal to or below zero. Please, make sure that you have entered a positive cash value. Enter a new cash amount : ";
			}
			else
			{
				customerList[i].setBalance(customerList[i].getBalance() + depositAmount); customerList[i].AccountTransactionCounter++;
				customerList[i].setATMBalanceAmount(customerList[i].getATMBalanceAmount() + depositAmount); 
				std::cout << "Currently, customer- " << i << "have " << customerList[i].getBalance() << "TL in his/her bank account.\n"; 
				break;
			}
		}

		if (customerList[i].getBalance() > 1'000'000)
		{
			customerList[i].setAccountVipStatus(true);
		}
	}

	SaveAccountInfo(customerList);
}

void WithdrawCurrency(std::vector<AccountOwner>& customerList)
{
	for (size_t i = 0; i < customerList.size(); i++)
	{
		std::cout << "How much TL will you withdraw from customer " << i + 1 << ": " << std::flush;
		
		while (true)
		{
			int withdrawAmount{};
			std::cin >> withdrawAmount;
			std::cin.clear();
			IgnoreBuffer();

			if (std::cin.fail())
			{
				std::cout << "You have entered an invalid cash amount. Please, make sure that you have entered a numeric value : ";
			}
			else if (withdrawAmount <= 0)
			{
				std::cout << "You have entered a valid input, but it was equal to or below zero. Please, make sure that you have entered a positive cash value. Enter a new cash amount : ";
			}
			else
			{
				if (customerList[i].getATMBalanceAmount() > static_cast<unsigned int>(withdrawAmount) && customerList[i].getBalance() >= static_cast<unsigned int>(withdrawAmount))
				{
					customerList[i].setBalance(customerList[i].getBalance() - withdrawAmount); customerList[i].AccountTransactionCounter++;
					customerList[i].setATMBalanceAmount(customerList[i].getATMBalanceAmount() - withdrawAmount); 
					std::cout << "Currently, customer -" << i + 1 << "- have " << customerList[i].getBalance() << "TL in his/her bank account.\n"; 
					break;
				}
				else
				{
					std::cout << "You do not have that much of cash money either in your account or in ATM.\n";
					std::cout << "Cash in ATM               : " << customerList[i].getATMBalanceAmount() << "\n";
					std::cout << "Cash in Your Account      : " << customerList[i].getBalance() << "\n";
					std::cout << "Cash you wish to withdraw : " << withdrawAmount << "\n";
					std::cout << "Enter Cash Amount Again   : ";
				}
			}
		}

		if (customerList[i].getBalance() <= 1'000'000)
		{
			customerList[i].setAccountVipStatus(false);
		}
	}

	SaveAccountInfo(customerList);
}

std::vector<AccountOwner>& CreateAccount(std::vector<AccountOwner>& customerList)
{
	unsigned int amount{};
	std::cout << "How many accounts will be created ? : ";
	std::cin >> amount;
	std::cin.clear();
	IgnoreBuffer();

	if (std::cin.fail())
	{
		std::cout << "Please, enter a numeric number!. Program is exiting."; exit(EXIT_FAILURE);
	}

	for (unsigned int counterList{}; counterList < amount; counterList++)
	{
		std::cout << "How would you like to create an account for the customer - " << counterList + 1 << "?\n";
		std::cout << "With predefined values : 1\n";
		std::cout << "With specific values   : 2\n";
		std::cout << "To Exit                : 0\n";
		std::cout << "Choice: ";

		unsigned int choice{};
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();
		
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
				unsigned int customerAccountBalance;
				unsigned int customerAccountPINCode;
				bool customerAccountVipStatus;

				std::cout << "Please, Enter " << counterList << "th Customer's Information:\n";
				std::cout << "Name:       "; std::cin >> customerName; std::cin.clear(); IgnoreBuffer();
				std::cout << "Surname:    "; std::cin >> customerSurame; std::cin.clear(); IgnoreBuffer();
				std::cout << "Address:    "; std::cin >> customerAddress; std::cin.clear(); IgnoreBuffer();
				std::cout << "Balance:    "; std::cin >> customerAccountBalance; std::cin.clear(); IgnoreBuffer();
				std::cout << "PIN Code:   "; std::cin >> customerAccountPINCode; std::cin.clear(); IgnoreBuffer();
				std::cout << "VIP Status: "; std::cin >> customerAccountVipStatus; std::cin.clear(); IgnoreBuffer();

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

	SaveAccountInfo(customerList);
	return customerList;
}

void ChangeAccountInfo(std::vector<AccountOwner>& customerList)
{
	std::cout << "Which piece of information would you like to change?\n";
	std::cout << "To Exit           : -1\n";
	std::cout << "To Change Name    : 1\n";
	std::cout << "To Change Surname : 2\n";
	std::cout << "To Change Address : 3\n";
	std::cout << "To Change PIN Code: 4\n";
	
	while (true)
	{
		int choice{};
		std::cout << "Choice to change info : ";
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a numeric value between (-1) and (4), except (9) : ";
		}
		else if (choice < -1)
		{
			std::cout << "Please, enter a numeric value between (-1) and (4), except (0) : ";
		}
		else
		{
			switch (choice)
			{
				case -1:
				{
					std::cout << "Exiting from the program.\n"; exit(EXIT_SUCCESS);
				}
				case 1:
				{
					for (size_t i = 0; i < customerList.size(); i++)
					{
						std::string Name;
						std::cout << "Enter the new name for customer -" << i + 1 << ": ";
						std::cin >> Name;
						std::cin.clear();
						IgnoreBuffer();

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
						std::cin.clear();
						IgnoreBuffer();

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
						std::cin.clear();
						IgnoreBuffer();

						customerList[i].setAddress(Address);
					}
					break;
				}
				case 4:
				{
					for (size_t i = 0; i < customerList.size(); i++)
					{
						int PinCode;
						std::string OldPinCode = std::to_string(customerList[i].getAccountPINCode());
						std::remove(OldPinCode.c_str());

						std::cout << "Enter the new PIN Code for customer -" << i + 1 << ": ";
						std::cin >> PinCode;
						std::cin.clear();
						IgnoreBuffer();
						customerList[i].setAccountPINCode(PinCode);
					}
					break;
				}
				default:
				{
					std::cout << "Please, enter a numeric value between (-1) and (4), except (0) : "; break;
				}
			}

			SaveAccountInfo(customerList); 
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
	std::cout << "< If you do not have any PIN code, or it is not reachable, please press 9999. >\n";
	
	while (true)
	{
		std::cout << "PinCode : ";
		short PinCode{};
		std::cin >> PinCode;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "You have entered an invalid input. Please, make sure that you have entered a numeric value.\n";
		}
		else if (PinCode < 0)
		{
			std::cout << "You have entered a valid input, but it was below zero. Please, make sure that you have entered a positive numeric value.\n";
		}
		else if (PinCode == 9999)
		{
			std::cout << "WIP" << std::endl; //TODO #1
		}
		else if (PinCode == 0)
		{
			std::cout << "WIP" << std::endl; //TODO #2
		}
		else
		{	
			ReadAccountInfo(PinCode, customerList);
			if (!customerList.empty())
			{
				std::cout << "Welcome => " << customerList[0].getName() << "!\n";
				std::cout << "What would you like to do?\n";
				std::cout << "To See Account Information : 1\n";
				std::cout << "To Deposit Cash            : 2\n";
				std::cout << "To Withdraw Cash           : 3\n";
				std::cout << "To Change Account Info.    : 4\n";
				std::cout << "To Exit                    : -1\n";

				while (true)
				{
					std::cout << "Choice to take action: ";
					short customerChoice{};
					std::cin >> customerChoice;
					std::cin.clear();
					IgnoreBuffer();

					if (std::cin.fail())
					{
						std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n";
					}
					else if (customerChoice < -1)
					{
						std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n";
					}
					else
					{
						switch (customerChoice)
						{
							case -1:
							{
								std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
							}
							case 1:
							{
								CheckAccountInfo(customerList); break;
							}
							case 2:
							{
								DepositCurrency(customerList); break;
							}
							case 3:
							{
								WithdrawCurrency(customerList); break;
							}
							case 4:
							{
								ChangeAccountInfo(customerList); break;
							}
							default:
							{
								std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n";
							}
						}
					}
				}
			}
			else
			{
				std::cout << "Such _" << PinCode << "_ Pin Code could not be found. Please make sure that you have entered a valid pin code.\n";
			}
		}
	}
}

std::vector<AccountOwner>& ReadAccountInfo(const int& PinCode, std::vector<AccountOwner>& customerList)
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

	return customerList;
}








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

std::unique_ptr<AccountOwner> CreateAccount(const int& PinCode)
{
	std::cout << "How would you like to create an account for the customer?\n";
	std::cout << "With specific values   :  1\n";
	std::cout << "To Exit                : -1\n";

	while (true)
	{
		std::cout << "Choice to create an account: ";
		int choice{};
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a numeric value either (-1) or (2).\n"; continue;
		}
		else if (choice == 0)
		{
			std::cout << "DO NOT ENTER (0)!!!\n" << choice << std::endl; continue; //TODO #3
		}
		else
		{
			switch (choice)
			{
			case 1:
			{
				std::cout << "Please, specify these values;\n";
				std::string customerName;
				std::string customerSurame;
				std::string customerAddress;
				unsigned int customerAccountBalance;
				unsigned int customerAccountPINCode = PinCode;

				std::cout << "Name:       "; std::cin >> customerName; std::cin.clear(); IgnoreBuffer();
				std::cout << "Surname:    "; std::cin >> customerSurame; std::cin.clear(); IgnoreBuffer();
				std::cout << "Address:    "; std::cin >> customerAddress; std::cin.clear(); IgnoreBuffer();
				std::cout << "Balance:    "; std::cin >> customerAccountBalance; std::cin.clear(); IgnoreBuffer();

				bool customerAccountVipStatus = (customerAccountBalance >= 1'000'000) ? true : false;

				std::unique_ptr<AccountOwner> customer_ptr = std::make_unique<AccountOwner>(customerName, customerSurame, customerAddress, customerAccountBalance, customerAccountPINCode, customerAccountVipStatus);

				return SaveAccountInfo(std::move(customer_ptr));

			}
			case -1:
			{
				std::cout << "No account were created. Program is exiting by request."; exit(EXIT_SUCCESS);
			}
			default:
			{
				std::cout << "Please, enter a numeric value between (-1) and (2), except (0) : "; continue;
			}
			}
		}
	}
}

std::unique_ptr<AccountOwner> ReadAccountInfo(const int& PinCode)
{
	std::unique_ptr<AccountOwner> customer = std::make_unique<AccountOwner>();

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
		std::cout << "Would you like to create a new one? [Y/N] : ";
		while (true)
		{
			char choice;
			std::cin >> choice;
			std::cin.clear();
			IgnoreBuffer();

			if (std::cin.fail())
			{
				std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
			}
			else if (choice == 0)
			{
				std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
			}
			else
			{
				switch (choice)
				{
					case 'y':
					case 'Y':
					{
						[[__fallthrough]];
						return CreateAccount(PinCode);
					}
					case 'n':
					case 'N':
					{
						[[__fallthrough]];
						std::cout << "Exiting from the program by request.\n"; exit(EXIT_SUCCESS);
					}
				default:
				{
					std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
				}
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
		std::cout << "PinCode : ";
		short PinCode{};
		std::cin >> PinCode;
		std::cin.clear();
		IgnoreBuffer();
		system("cls");

		if (std::cin.fail() || PinCode < 0)
		{
			std::cout << "You have entered an invalid input. Please, make sure that you have entered a numeric value.\n"; continue;
		}
		else if (PinCode == 0)
		{
			std::cout << "DO NOT ENTER (0) OR ALPHABETIC CHARACTER!!!\n" << std::endl; continue;
		}
		else
		{
			while (true)
			{
				system("cls");
				std::unique_ptr<AccountOwner> customer = ReadAccountInfo(PinCode);
				std::cout << "Welcome => " << customer->getName() << "!\n";
				std::cout << "\nWhat would you like to do?\n";
				std::cout << "To See Account Information : 1\n";
				std::cout << "To Deposit Cash            : 2\n";
				std::cout << "To Withdraw Cash           : 3\n";
				std::cout << "To Change Account Info.    : 4\n";
				std::cout << "To Exit                    : -1\n";
				std::cout << "Choice to take action: ";
				short customerChoice{};
				std::cin >> customerChoice;
				std::cin.clear();
				IgnoreBuffer();

				if (std::cin.fail())
				{
					std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n"; continue;
				}
				else if (customerChoice < -1)
				{
					std::cout << "Please, enter a numeric value between (-1) and (4), except (0)\n"; continue;
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
							CheckAccountInfo(std::move(customer)); break;
						}
						case 2:
						{
							DepositCurrency(std::move(customer)); break;
						}
						case 3:
						{
							WithdrawCurrency(std::move(customer)); break;
						}
						case 4:
						{
							ChangeAccountInfo(PinCode); break;
						}
					}
				}
			}
		}
		break;
	}
}

void CheckAccountInfo( std::unique_ptr<AccountOwner> customer)
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
	std::cout << "Total Amount of Transaction: " << customer->AccountTransactionCounter << std::endl;
	std::cout << "=============================================" << std::endl;
	std::cout << "Would you like to continue[y], or exit[n]? : ";
	while (true)
	{
		char choice;
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
		}
		else
		{
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
					std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
				}
			}
		}
		break;
	}
}

void DepositCurrency(std::unique_ptr<AccountOwner> customer)
{
	std::cout << "How much TL will you deposit to? : " << std::flush;
		
	while (true)
	{
		int depositAmount{};
		std::cin >> depositAmount;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail() || depositAmount <= 0)
		{
			std::cout << "You have entered an invalid cash amount. Please, make sure that you have entered a positive numeric value : "; continue;
		}
		else
		{
			customer->setBalance(customer->getBalance() + depositAmount); customer->AccountTransactionCounter++;
			customer->setATMBalanceAmount(customer->getATMBalanceAmount() + depositAmount);
			std::cout << "Currently, customer have " << customer->getBalance() << "TL in his/her bank account.\n";
			break;
		}
	}

	if (customer->getBalance() > 1'000'000)
	{
		customer->setAccountVipStatus(true);
	}
	
	SaveAccountInfo(std::move(customer));

	std::cout << "Would you like to continue[y], or exit[n]? : ";
	while (true)
	{
		char choice;
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
		}
		else
		{
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
					std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
				}
			}
		}
		break;
	}
}

void WithdrawCurrency(std::unique_ptr<AccountOwner> customer)
{
	std::cout << "How much TL will you withdraw from? : " << std::flush;
		
	while (true)
	{
		int withdrawAmount{};
		std::cin >> withdrawAmount;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail() || withdrawAmount <= 0)
		{
			std::cout << "You have entered an invalid cash amount. Please, make sure that you have entered a positive numeric value : "; continue;
		}
		else
		{
			if (customer->getATMBalanceAmount() >= static_cast<unsigned int>(withdrawAmount) && customer->getBalance() >= static_cast<unsigned int>(withdrawAmount))
			{
				customer->setBalance(customer->getBalance() - withdrawAmount); customer->AccountTransactionCounter++;
				customer->setATMBalanceAmount(customer->getATMBalanceAmount() - withdrawAmount);
				std::cout << "Currently, customer have " << customer->getBalance() << "TL in his/her bank account.\n";
				break;
			}
			else
			{
				std::cout << "You do not have that much of cash money either in your account or in ATM.\n";
				std::cout << "Cash in ATM               : " << customer->getATMBalanceAmount() << "\n";
				std::cout << "Cash in Your Account      : " << customer->getBalance() << "\n";
				std::cout << "Cash you wish to withdraw : " << withdrawAmount << "\n";
				std::cout << "Enter Cash Amount Again   : "; 
				continue;
			}
		}
	}

	if (customer->getBalance() <= 1'000'000)
	{
		customer->setAccountVipStatus(false);
	}

	SaveAccountInfo(std::move(customer));

	std::cout << "Would you like to continue[y], or exit[n]? : ";
	while (true)
	{
		char choice;
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
		}
		else
		{
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
					std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
				}
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
		std::cout << "To Exit           : -1\n";
		std::cout << "To Change Name    : 1\n";
		std::cout << "To Change Surname : 2\n";
		std::cout << "To Change Address : 3\n";
		std::cout << "To Change PIN Code: 4\n";
		std::cout << "To Go to Main Menu: 5\n";
		int choice{};
		std::cout << "Choice to change info : ";
		std::cin >> choice;
		std::cin.clear();
		IgnoreBuffer();

		if (std::cin.fail())
		{
			std::cout << "Please, enter a numeric value between (-1) and (4), except (0) : "; continue;
		}
		else if (choice < -1)
		{
			std::cout << "Please, enter a numeric value between (-1) and (4), except (0) : "; continue;
		}
		else
		{
			switch (choice)
			{
				case -1:
				{
					std::cout << "Exiting from the program.\n"; exit(EXIT_SUCCESS);
				}
				case 5:
				{
					return 1;
				}
				case 1:
				{
					std::string Name;
					std::cout << "Enter the new name for customer:";
					std::cin >> Name;
					std::cin.clear();
					IgnoreBuffer();

					customer->setName(Name);
					std::cout << "Your name has been changed. Your new name is : " << customer->getName() << std::endl;
					SaveAccountInfo(std::move(customer));

					std::cout << "Would you like to change another information, or come back to main menu?\n";
					std::cout << "(Y/y) : To change another information,\n";
					std::cout << "(N/n) : To come back to main menu,\n";

					while (true)
					{
						char choice;
						std::cin >> choice;
						std::cin.clear();
						IgnoreBuffer();

						if (std::cin.fail())
						{
							std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
						}
						else
						{
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
						}
						break;
					} 
					 continue;
				}
				case 2:
				{
					std::string Surname;
					std::cout << "Enter the new surname for customer:";
					std::cin >> Surname;
					std::cin.clear();
					IgnoreBuffer();

					customer->setSurname(Surname);
					std::cout << "Your surname has been changed. Your new surname is : " << customer->getSurname() << std::endl;
					SaveAccountInfo(std::move(customer));

					std::cout << "Would you like to change another information, or come back to main menu?\n";
					std::cout << "(Y/y) : To change another information,\n";
					std::cout << "(N/n) : To come back to main menu,\n";

					while (true)
					{
						char choice;
						std::cin >> choice;
						std::cin.clear();
						IgnoreBuffer();

						if (std::cin.fail())
						{
							std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
						}
						else
						{
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
						}
						break;
					}
					 continue;
				}
				case 3:
				{
					std::string Address;
					std::cout << "Enter the new address for customer:";
					std::cin >> Address;
					std::cin.clear();
					IgnoreBuffer();

					customer->setAddress(Address);
					std::cout << "Your address has been changed. Your new address is : " << customer->getAddress() << std::endl;
					SaveAccountInfo(std::move(customer));

					std::cout << "Would you like to change another information, or come back to main menu?\n";
					std::cout << "(Y/y) : To change another information,\n";
					std::cout << "(N/n) : To come back to main menu,\n";

					while (true)
					{
						char choice;
						std::cin >> choice;
						std::cin.clear();
						IgnoreBuffer();

						if (std::cin.fail())
						{
							std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
						}
						else
						{
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
						}
						break;
					}
					 continue;
				}
				case 4:
				{
					int temp_PinCode;
					std::string OldPinCode = std::to_string(customer->getAccountPINCode());
					std::remove(OldPinCode.c_str());

					std::cout << "Enter the new Pin Code for customer:";
					std::cin >> temp_PinCode;
					std::cin.clear();
					IgnoreBuffer();

					customer->setAccountPINCode(temp_PinCode);
					std::cout << "Your PIN Code has been changed. Your new PIN Code is : " << customer->getAccountPINCode() << std::endl;
					SaveAccountInfo(std::move(customer));

					std::cout << "Would you like to change another information, or come back to main menu?\n";
					std::cout << "(Y/y) : To change another information,\n";
					std::cout << "(N/n) : To come back to main menu,\n";

					while (true)
					{
						char choice;
						std::cin >> choice;
						std::cin.clear();
						IgnoreBuffer();

						if (std::cin.fail())
						{
							std::cout << "Please, enter a char of 'Y' or 'N': "; continue;
						}
						else
						{
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
						}
						break;
					}
				 continue;
				}
				default:
				{
					std::cout << "Please, enter a numeric value between (-1) and (4), except (0) : "; break;
				}
			}
		}
	}
}


std::unique_ptr<AccountOwner> SaveAccountInfo( std::unique_ptr<AccountOwner> customer)
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












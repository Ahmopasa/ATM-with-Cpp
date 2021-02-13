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

	AccountVipStatus = false;

	std::cout << ++AccountTransactionCounter << " - " << "Constructor for AccountOwner, with predetermined values, was called." << std::endl;

}

AccountOwner::AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, int& tempBalance, int& tempPINCode, bool tempVipStatus) : Name{ tempName }, Surname{ tempSurname }, Address{ tempAddress }, AccountBalance{ tempBalance }, AccountPINCode{ tempPINCode }, AccountVipStatus{ tempVipStatus }
{
	std::cout << ++AccountTransactionCounter << " - " << "Constructor for AccountOwner, with desired values, was called." << std::endl;
}

AccountOwner::AccountOwner(const AccountOwner& tempObj)
{

	Name = tempObj.Name;
	Surname = tempObj.Surname;
	Address = tempObj.Address;

	AccountBalance = tempObj.AccountBalance;
	AccountPINCode = tempObj.AccountPINCode;

	AccountVipStatus = tempObj.AccountVipStatus;

	std::cout << ++AccountTransactionCounter << " - " << "Copy Constructor for AccountOwner was called." << std::endl;
}

AccountOwner::~AccountOwner()
{
	std::cout << AccountTransactionCounter-- << "th Deconstruction was called" << std::endl;
}

void CheckAccountInfo(const AccountOwner& tempObjective)
{
	std::cout << "Name: " << tempObjective.getName() << std::endl;
	std::cout << "Surname: " << tempObjective.getSurname() << std::endl;
	std::cout << "Address: " << tempObjective.getAddress() << std::endl;
	std::cout << "AccountBalance: " << tempObjective.getBalance() << std::endl;
	std::cout << "AccountPINCode: " << tempObjective.getAccountPINCode() << std::endl;
	std::cout << "AccountVipStatus: " << std::boolalpha << tempObjective.getAccountVipStatus() << std::endl;

}

void DepositCurrency(AccountOwner& tempObjective)
{
	std::cout << "How much TL will you deposit to your current account?: " << std::flush;
	int depositAmount {};
	std::cin >> depositAmount;

	tempObjective.setBalance(tempObjective.getBalance() + depositAmount);

	std::cout << "Currently, you have " << tempObjective.getBalance() << "TL in your bank account.\n";

}

void WithdrawCurrency(AccountOwner& tempObjective)
{
	std::cout << "How much TL will you withdraw to your current account?: " << std::flush;
	int withdrawAccount{};
	std::cin >> withdrawAccount;
	
	tempObjective.setBalance(tempObjective.getBalance() - withdrawAccount);

	std::cout << "Currently, you have " << tempObjective.getBalance() << "TL in your bank account.\n";
}

std::vector<AccountOwner>& CreateAccount(unsigned int amount, std::vector<AccountOwner>& customerList)
{
	std::cout << "How would you like to create an account?\n";
	std::cout << "1. With predefined values.\n";
	std::cout << "2. With specific values.\n";
	std::cout << "0. To Exit.\n";

	unsigned int choice{};
	std::cin >> choice;

	switch (choice)
	{
	case 1: 
	{
		std::cout << "An account with predefined values has been created.\n";
		for (size_t i = 0; i < amount; i++)
		{
			AccountOwner customer;
			customerList.push_back(customer);
		}
		return customerList;
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

		for (size_t i = 0; i < amount; i++)
		{
			std::cout << "Please, Enter " << i << "th Customer's Information:\n";
			std::cout << "Name:       "; std::cin >> customerName;
			std::cout << "Surname:    "; std::cin >> customerSurame;
			std::cout << "Address:    "; std::cin >> customerAddress;
			std::cout << "Balance:    "; std::cin >> customerAccountBalance;
			std::cout << "PIN Code:   "; std::cin >> customerAccountPINCode;
			std::cout << "VIP Status: "; std::cin >> customerAccountVipStatus;

			AccountOwner customer{ customerName , customerSurame , customerAddress , customerAccountBalance , customerAccountPINCode , customerAccountVipStatus };

			customerList.push_back(customer);
		}
		return customerList;
	}
	case 0:
	{
		std::cout << "No account were created.\n"; 
		return customerList;
	}
	default:
	{
		std::cout << "Please, enter a number mentioned above.\nProgram is exiting.";
		break;
	}
	}

	return customerList;
}


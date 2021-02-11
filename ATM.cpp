#include "ATM.h"

int AccountOwner::AccountTransactionCounter{0};

AccountOwner::AccountOwner(void)
{
	Name = "NoName";
	Surname = "NoSurname";
	Address = "NoAddress";

	int AccountBalance = 0;
	int AccountPINCode = 0;

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
	
}

std::string& AccountOwner::getName()
{
	return Name;
}

std::string& AccountOwner::getSurname()
{
	return Surname;
}

std::string& AccountOwner::getAddress()
{
	return Address;
}

void AccountOwner::setName(const std::string& tempName)
{
	Name = tempName;
}

void AccountOwner::setSurname(const std::string& tempSurname)
{
	Surname = tempSurname;
}

void AccountOwner::setAddress(const std::string& tempAddress)
{
	Address = tempAddress;
}

int& AccountOwner::getBalance()
{
	return AccountBalance;
}

void AccountOwner::setBalance(const int& tempBalance)
{
	AccountBalance = tempBalance;
}

int& AccountOwner::getAccountPINCode()
{
	return AccountPINCode;
}

void AccountOwner::setAccountPINCode(const int& tempPINCode)
{
	AccountPINCode = tempPINCode;
}

bool& AccountOwner::getAccountVipStatus()
{
	return AccountVipStatus;
}

void AccountOwner::setAccountVipStatus(const bool& tempVipStatus)
{
	AccountVipStatus = tempVipStatus;
}

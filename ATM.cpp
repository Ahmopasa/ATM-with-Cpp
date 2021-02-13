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


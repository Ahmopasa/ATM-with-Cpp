#ifndef ATM_H_
#define ATM_H_

#include <iostream>
#include <string>


class AccountOwner
{
private:
	std::string Name;
	std::string Surname;
	std::string Address;

	int AccountBalance;
	int AccountPINCode;

	bool AccountVipStatus;

	static int AccountTransactionCounter;

public:

	const std::string& getName(void) const;
	void setName(const std::string&);

	const std::string& getSurname(void) const;
	void setSurname(const std::string&);

	const std::string& getAddress(void) const;
	void setAddress(const std::string&);

	const int& getBalance(void) const;
	void setBalance(const int&);

	const int& getAccountPINCode(void) const; 
	void setAccountPINCode(const int&);

	const bool& getAccountVipStatus(void) const;
	void setAccountVipStatus(const bool&);


public:
	AccountOwner(void);
	AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, int& tempBalance, int& tempPINCode, bool tempVipStatus = false);
	AccountOwner(const AccountOwner&);
	~AccountOwner();
};

void CheckAccountInfo(const AccountOwner& tempObjective);
void DepositCurrency(); //TODO #1
void WithdrawCurrency(); //TODO #2
//void CreateAccount(); //TODO #3

//void ChangeAccountInfo(); //TODO #4

#endif
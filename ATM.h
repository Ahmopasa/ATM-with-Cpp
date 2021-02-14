#ifndef ATM_H_
#define ATM_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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

void CheckAccountInfo(const std::vector<AccountOwner>&);
void DepositCurrency(std::vector<AccountOwner>&);
void WithdrawCurrency(std::vector<AccountOwner>&);
std::vector<AccountOwner>& CreateAccount(const unsigned int, std::vector<AccountOwner>&);
void ChangeAccountInfo(std::vector<AccountOwner>&); 
void SaveAccountInfo(const std::vector<AccountOwner>&); //TODO #5

#endif
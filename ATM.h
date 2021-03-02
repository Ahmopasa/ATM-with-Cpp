#ifndef ATM_H_
#define ATM_H_

#ifdef __cplusplus

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class ATM
{
private:
	unsigned int ATMBalanceAmount;

public:
	ATM();
	~ATM();

	const unsigned int& getATMBalanceAmount(void) const;
	void setATMBalanceAmount(const unsigned int&);
};

class AccountOwner : public ATM
{
private:
	std::string Name;
	std::string Surname;
	std::string Address;

	unsigned int AccountBalance;
	unsigned int AccountPINCode;

	bool AccountVipStatus;

public:
	static int AccountTransactionCounter;

public:
	const std::string& getName(void) const;
	void setName(const std::string&);

	const std::string& getSurname(void) const;
	void setSurname(const std::string&);

	const std::string& getAddress(void) const;
	void setAddress(const std::string&);

	const unsigned int& getBalance(void) const;
	void setBalance(const unsigned int&);

	const unsigned int& getAccountPINCode(void) const; 
	void setAccountPINCode(const unsigned int&);

	const bool& getAccountVipStatus(void) const;
	void setAccountVipStatus(const bool&);

	AccountOwner(void);
	AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, unsigned int& tempBalance, unsigned int& tempPINCode, bool tempVipStatus = false);
	AccountOwner(const AccountOwner&);
	~AccountOwner();
};

std::unique_ptr<AccountOwner> CreateAccount(const int&);
std::unique_ptr<AccountOwner> ReadAccountInfo(const int&);
void UserScreen(void);
void CheckAccountInfo( std::unique_ptr<AccountOwner>);
void DepositCurrency(std::unique_ptr<AccountOwner>);
void WithdrawCurrency(std::unique_ptr<AccountOwner>);
int ChangeAccountInfo(const int&);
std::unique_ptr<AccountOwner> SaveAccountInfo(std::unique_ptr<AccountOwner>);

#endif 
#endif // ATM_H_
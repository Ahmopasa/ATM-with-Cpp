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

void CheckAccountInfo(const std::unique_ptr<AccountOwner>);
void DepositCurrency(std::unique_ptr<AccountOwner>);
void WithdrawCurrency(std::unique_ptr<AccountOwner>);
std::unique_ptr<AccountOwner> CreateAccount(const int&);
void ChangeAccountInfo(std::unique_ptr<AccountOwner>);
void SaveAccountInfo(const std::unique_ptr<AccountOwner>);
void UserScreen(void);
std::unique_ptr<AccountOwner> ReadAccountInfo(const int&);

#endif
 
#endif // ATM_H_
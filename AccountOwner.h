#pragma once

#include <string>

class AccountOwner
{
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

	AccountOwner(void) = default;
	AccountOwner(const std::string& tempName, const std::string& tempSurname, const std::string& tempAddress, const unsigned int& tempBalance, const unsigned int& tempPINCode, const bool tempVipStatus = false);
	AccountOwner(const AccountOwner&);
	~AccountOwner();

private:
	std::string Name{ "NoName" };
	std::string Surname{ "NoSurname" };
	std::string Address{ "NoAddress" };

	unsigned int AccountBalance{ 0 };
	unsigned int AccountPINCode{ 0 };

	bool AccountVipStatus{ 0 };
};
#ifndef ATM_H_
#define ATM_H_

#include <string> 
#include <iostream>

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

private:
    std::string& getName();
    void setName(const std::string&);

    std::string& getSurname();
    void setSurname(const std::string&);

    std::string& getAddress();
    void setAddress(const std::string&);

    int& getBalance();
    void setBalance(const int&);

    int& getAccountPINCode();
    void setAccountPINCode(const int&);

    bool& getAccountVipStatus();
    void setAccountVipStatus(const bool&);



public:
    AccountOwner();
    AccountOwner(std::string& tempName, std::string& tempSurname, std::string& tempAddress, int& tempBalance, int& tempPINCode, bool tempVipStatus = false);
    AccountOwner(const AccountOwner&);
    ~AccountOwner();

    void DepositCurrency(AccountOwner&);
    void WithdrawCurrency(AccountOwner&);
    void CheckAccountInfo(const AccountOwner&);
    void ChangeAccountInfo();

};




#endif
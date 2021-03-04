#pragma once

#include <memory>

#include "AccountOwner.h"
#include "ATM.h"

std::unique_ptr<AccountOwner> CreateAccount(const int&);
std::unique_ptr<AccountOwner> ReadAccountInfo(const int&);
void UserScreen(void);
void CheckAccountInfo(std::unique_ptr<AccountOwner>);
void DepositCurrency(std::unique_ptr<AccountOwner>);
void WithdrawCurrency(std::unique_ptr<AccountOwner>);
int ChangeAccountInfo(const int&);
std::unique_ptr<AccountOwner> SaveAccountInfo(std::unique_ptr<AccountOwner>);

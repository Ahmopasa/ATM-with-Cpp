#include "ATM.h"

int main()
{


	std::vector<AccountOwner> customerList;

	CreateAccount(2, customerList);

	//CheckAccountInfo(customerList);

	//DepositCurrency(customerList);

	//WithdrawCurrency(customerList);

	ChangeAccountInfo(customerList);

	CheckAccountInfo(customerList);


	return 0;
}
#include "ATM.h"

int main()
{


	std::vector<AccountOwner> customerList;

	CreateAccount(1, customerList);

	//CheckAccountInfo(customerList);

	//DepositCurrency(customerList);

	//WithdrawCurrency(customerList);

	//ChangeAccountInfo(customerList);

	//CheckAccountInfo(customerList);

	SaveAccountInfo(customerList);

	return 0;
}
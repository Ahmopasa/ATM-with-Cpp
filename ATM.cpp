#include "ATM.h"

ATM::~ATM()
{
}

const unsigned int& ATM::getATMBalanceAmount(void) const
{
	return ATMBalanceAmount;
}

void ATM::setATMBalanceAmount(const unsigned int& tempBalance)
{
	ATMBalanceAmount = tempBalance;
}














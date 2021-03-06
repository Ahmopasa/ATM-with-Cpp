#pragma once

class ATM
{
public:
	ATM() = default;
	~ATM();

	const unsigned int& getATMBalanceAmount(void) const;
	void setATMBalanceAmount(const unsigned int&);

private:
	unsigned int ATMBalanceAmount{ 1'000'000 };
};
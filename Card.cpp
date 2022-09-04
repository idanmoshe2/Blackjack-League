#include "Card.h"

Card::Card(int digit, const string symbol) :
	value(digit > 10? 10 : digit), symbol(symbol), digit(digit) {}

Card::Card(Card& other) :
	value(other.digit > 10 ? 10 : other.digit), symbol(other.symbol), digit(other.digit) {}

Card::~Card()
{

}


void Card::print_card()
{
	string sign = " ";
	if (digit > 10 || digit == 1)
	{
		if (digit == 11)
			sign = 'J';
		if (digit == 12)
			sign = 'Q';
		if (digit == 13)
			sign = 'K';
		if (digit == 1)
			sign = 'A';
		cout << sign << " ";
	}
	else
	{
		cout << digit << " ";
	}
}

ostream& operator<<(ostream& os, const Card& c)
{
	os << c.digit;
	return os;
}

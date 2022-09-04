#include "Stats.h"


Stats::Stats(unsigned int wins, unsigned int loses, unsigned int num_of_bjs, unsigned int bust, double highest_balance, double lowest_balance, unsigned int ties) :
	wins(wins), loses(loses), num_of_bjs(num_of_bjs), bust(bust), highest_balance(highest_balance), lowest_balance(lowest_balance), ties(ties) {}

void Stats::check_highest_balance(double num)
{
	if (num > highest_balance)
		highest_balance = num;
}

void Stats::check_lowest_balance(double num)
{
	if (num < lowest_balance)
		lowest_balance = num;
}

ostream& operator<<(ostream& os, const Stats& s)
{
	os << s.wins;
	return os;
}

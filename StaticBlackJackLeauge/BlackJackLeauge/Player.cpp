#include "Player.h"

unsigned int Player::human_cnt(0);

Player::Player(const string& name, char type) : name(name), type(type), league(league), player_stats(player_stats), blackjack_flag(blackjack_flag), bust_flag(bust_flag), season_balance(season_balance) {

	try
	{
		player_stats = new Stats(0, 0, 0, 0, 0, get_round_balance(), 0);
	}
	catch (std::bad_alloc& e)
	{
		cout << e.what() << endl;
		return;
	}
	if (!player_stats)
		return;
	
}


Player::Player(Player& other) :
	name(other.name), type(other.type), league(other.league), player_stats(other.player_stats), blackjack_flag(other.blackjack_flag), bust_flag(other.bust_flag), season_balance(other.season_balance) {}

Player::~Player() {

	if (cards.size() > 0)
	{
		for (auto it = cards.begin(); it != cards.end(); it++)
			delete (*it);
	}

	if (player_stats)
		delete player_stats;
}
 


void Player::delete_cards()
{
	for (auto it = cards.begin(); it != cards.end(); it++)
		delete (*it);

	if (cards.size() > 0)
	{
		cards.clear();
	}
}

ostream& operator<<(ostream& os, const Player& p)
{
	os << p.player_stats;
	return os;
}


int Human_Player::choose_a_play(unsigned int idx)
{
	unsigned int action = 0;
	do
	{
		cin >> action;
		if (action < 1 || action > idx)
			cout << "bad input." << endl << "input must be between 1 to " << idx << ". try again: ";
	} while (action<1 || action>idx);
	return action;
}

int Bot_Player::choose_a_play(unsigned int idx)
{
	unsigned int action = 0;
	do
	{
		 action = (rand() % idx) + 1;
	} while (action<1 || action>idx);
	return action;
}

int Dealer::choose_a_play(unsigned int idx)
{
	unsigned int action = 0;
	do
	{
		action = (rand() % idx) + 1;
	} while (action<1 || action>idx);
	return action;
}


void Player::insert_card(Card* c)
{
	this->cards.push_back(c);
}

void Player::print_single_hand_card(unsigned int idx)
{
	if (idx <= cards.size())
		cards[idx]->print_card();
	else
		cout << "ERROR, idx is not existed in this hand." << endl;
}

void Player::update_sum_card()
{
	unsigned int temp_sum = 0;
	unsigned int i = 0;
	bool ace = false;
	for (i = 0; i < cards.size(); i++)
	{
		temp_sum += cards[i]->get_value();
		if (cards[i]->get_digit() == 1)
			ace = true;
	}
	if (ace && (temp_sum + 10 < 22))
		temp_sum = temp_sum + 10;
	sum_card = temp_sum;
}

void Player::check_if_bj()
{
	update_sum_card();
	if (sum_card == BLACKJACK)
		blackjack_flag = true;
	else
		blackjack_flag = false;
}

void Player::print_current_hand()
{
	if (cards.size() > 0)
	{
		cout << "[ ";
		for (unsigned int i = 0; i < cards.size(); i++)
		{
			if (i > 0)
				cout << " , ";
			cards[i]->print_card();
		}
		cout << "] " << endl;
	}
}

void Player::reset_balance(double num)
{
	round_balance = num;
}





#ifndef PLAYER_H
#define PLAYER_H
#include "Deck.h"
#include "Game.h"
#include "Card.h"
#include "Stats.h"
#include "League.h"
#include<iostream>
#include<string>
#define BLACKJACK 21
#define INITIAL_ROUND_BALANCE 100
using namespace std;
class Deck;
class Stats;
class Card;
class Game;
class League;

class Player
{

protected:
	string name; // player's name
	char type; //player's type ('H' - Human, 'B' - Bot, 'D' - Dealer)
	vector<Card*> cards; // player's card's hand 
	League* league; //pointer for League class
	double round_balance = 0; //player's balance from last round
	double bet = 0; //players bet
	Stats* player_stats; //pointer for Stats class
	unsigned int sum_card = 0; //player's hand's sum value
	bool blackjack_flag = false; //player got a blackjack
	bool bust_flag = false; //player busted
	bool win_flag = false; //player won
	bool tie_flag = false; // player got a tie
	double season_balance = 0; //player's balance from last season
	double league_balance = 0; //player's balance from last league
	Game* game; //pointer for Game class
	static unsigned int human_cnt; //static variable for human players

public:
	Player(const string& name, char type); //const
	Player(Player& other); // CC
	~Player(); // destructor
	void delete_cards(); //reset players card
	string get_name() const { return name; }; //get players name
	void set_name(string set_name) { name = set_name; }; // set player name
	double get_round_balance() { return round_balance; }; // get round balance
	double get_season_balance() { return season_balance; }; // get season balance
	double get_league_balance() { return league_balance; }; // get league balance
	void set_round_balance(double num) { round_balance += num; }; // set round balance
	void set_season_balance(double num) { season_balance += num; }; // set season balance
	void set_league_balance(double num) { league_balance += num; }; // set league balance
	void reset_season_balance(double num) { season_balance = num; }; // reset season balance
	vector<Card*> get_cards() { return cards; }; // get cards
	void insert_card(Card* c); // insert cards
	virtual int choose_a_play(unsigned int idx) = 0; // choose a move
	void set_bet(double idx) { bet = idx; }; // set a players bet
	double get_bet() { return bet; }; // get players bet
	void print_single_hand_card(unsigned int idx); //prints single hand card
	int get_hand_len() { return cards.size(); }; // get len of hand
	void update_sum_card(); // update sum of cards
	void check_if_bj(); // check if got blackjack
	bool get_blackjack_flag() { return blackjack_flag; }; //get blackjack flag
	void set_blackjack_flag(bool flag) { blackjack_flag = flag; }; // set blackjack flag
	unsigned int get_sum_card() { return sum_card; }; //get sum card
	void print_current_hand(); // print current hand
	int get_card(int idx) { return cards[idx]->get_digit(); }; // get players specific card
	bool get_bust_flag() { return bust_flag; }; // get flag for bust
	void set_bust_flag(bool flag) { bust_flag = flag; }; // set flag for bust
	void set_win_flag(bool flag) { win_flag = flag; }; // set win flag 
	bool get_win_flag() { return win_flag; }; // get win flag
	void set_tie_flag(bool flag) { tie_flag = flag; }; // set tie flag
	bool get_tie_flag() { return tie_flag; }; // get tie flag 
	Stats* get_player_stats() { return player_stats; }; // get players ptr for Stats class
	char get_type() { return type; }; // get players type
	friend ostream& operator<<(ostream& os, const Player& p); //operator overload
	void reset_balance(double num); //reset balance to the input value
	Game* get_game() { return game; }; //get game ptr
	static unsigned int get_human_cnt() { return human_cnt; }; // get static human counter



};

class Human_Player : public Player {
public:
	Human_Player(const string& name, char type) : Player(name, type) { human_cnt++; }; //constructor
	Human_Player(Human_Player& other) : Player(other) {}; //CC
	int choose_a_play(unsigned int idx); //choose a move from 1 to idx (manually)
};

class Bot_Player : public Player {
public:
	Bot_Player(const string& name, char type) : Player(name, type) {};//constructor
	Bot_Player(Bot_Player& other) : Player(other) {}; //CC
	int choose_a_play(unsigned int idx); //choose a move from 1 to idx (automatically)
};

class Dealer : public Bot_Player {
public:
	Dealer(const string& name, char type) : Bot_Player(name, type) {};//constructor
	Dealer(Dealer& other) : Bot_Player(other) {}; //CC
	int choose_a_play(unsigned int idx); //choose a move from 1 to idx (automatically)
};

#endif
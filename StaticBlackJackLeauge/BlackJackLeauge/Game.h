#ifndef GAME_H
#define GAME_H
#include "Deck.h"
#include "Player.h"
#include "League.h"

#define DEALER_MIN 17
using namespace std;

class Player;
class Human_Player;
class Bot_Player;
class Dealer;
class Deck;
class Card;
class League;

class Game
{
protected:

	int limit_of_hands = 2; //number of hands per round.
	vector<Player*> players; //an array of all the players in the game.
	vector<int> active_players; //an array of all the active players in the game (with balance higher than 0).
	double prize = -1; //the amount of money each player get in each win case.
	bool house_win_flag = true; // flag for dealer's win.
	int current_hand_idx = 0; //counter for hands in the league.
	Deck* deck; //ptr for Deck class.
	Card* card; //ptr for Card class.
	int num_of_players = 0; //number of players in the league.

public:

	Game(vector<Player*> players, int num_of_players);// ctor
	~Game(); //dector
	void start_game(); //start game
	void set_num_of_players(int num) { num_of_players = num; }; //set number of players
	int get_num_of_players() { return num_of_players; }; // get number of players
	vector<Player*> get_players() { return players; }; // get players array
	void user_bet(); // set players bets
	void draw_first_two_cards(); //draw first two cards in game
	void pre_game_print(); // print every players bet and first drawed cards
	void dealer_has_blackjack(); //dealer got blackjack case
	void player_turn(); // player's turn	
	void dealer_turn(); // dealer's turn
	void print_game_summary(); //print summary of hand in game
	void reset_game(); //reset game stats and players flags
	void gameplay(); //gameplay of the game
	void check_who_plays(); //update active players array
	void reset_active_players(); // reset active players array
	void reset_deck(); //reset deck
	friend ostream& operator<<(ostream& os, const Game& g); //operator overload
	void pay_to_dealer(Player* p); //pay to dealer




};
#endif
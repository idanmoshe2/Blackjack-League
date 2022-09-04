#ifndef SEASON_H
#define SEASON_H
#include <iostream>
#include <string>
#include "Stats.h"
#include "Round.h"
#define NUM_OF_ROUNDS 1
using namespace std;
class Player;
class Round;
class Season
{
private:
	int season_num = 0; //counter for seasons for this league
	vector<Player*> players; //an array of players in this league
	vector<Round*> rounds; //an array for each round
	int num_of_rounds = 0; //number of rounds
	int current_round_idx; //current round index
	Stats* season_stats; // ptr for Stats class
	int num_of_players; //number of players in this league
public:
	Season(int season_num, vector<Player*> players, int num_of_players); //constructor
	Season(Season& other); //CC
	~Season(); //destructor
	void start_season(); //start season
	int get_round_idx() { return current_round_idx; }; // get round index
	void set_round_idx(int num) { current_round_idx = num; };//set round index
	void set_season_num(int num) { season_num = num; }; // set season number
	void set_num_of_rounds(int num) { num_of_rounds = num; }; // set num of rounds
	friend ostream& operator<<(ostream& os, const Season& s); //operator overload


};
#endif
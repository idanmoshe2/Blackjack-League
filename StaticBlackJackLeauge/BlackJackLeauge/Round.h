#ifndef ROUND_H
#define ROUND_H
#include "Stats.h"
#include "Game.h"
#include <iostream>
#include <string>
using namespace std;
class Game;
class Player;
class Stats;
class Round
{
private:
	int round_num = 0; //idx for round number
	Game* game; //pointer for class Game
	vector<Player*> players; //array of players
	Stats* round_stats; //ptr for class Stat
	int num_of_players; //number of players in the league




public:
	Round(int round_num, vector<Player*> players, int num_of_players); //ctor
	Round(Round& other); //CC
	~Round(); //detor
	void start_round(); //start round
	int get_round_num() { return round_num; }; //get round number
	void set_round_num(int num) { round_num = num; }; //set round number
	friend ostream& operator<<(ostream& os, const Round& r); //operator overload

};
#endif
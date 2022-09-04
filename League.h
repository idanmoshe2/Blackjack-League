#ifndef LEAGUE_H
#define LEAGUE_H

#include <fstream>
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <string.h>
#define MAX_PARTICIPANTS 7
#define NUM_OF_SEASONS 2
#define NAME 0
#define TYPE 1
#define SEASON_BALANCE 2
#define LEAGUE_BALANCE 3
#define NUMBER_OF_WINS 4
#define NUMBER_OF_BLACKJACKS 5
#define NUMBER_OF_LOSES 6
#define NUMBER_OF_TIES 7
#define NUMBER_OF_BUSTS 8
#define HIGHTEST_BALANCE 9
#define NUM_OF_HANDS_PLAYED 10
#define SEASON_IDX 0
#define ROUND_IDX 1



#include <vector>
#include "Stats.h"
#include "Player.h"
#include "Season.h"
using namespace std;
class Player;
class Dealer;
class Human_Player;
class Bot_Player;
class Stats;
class Season;
class League
{
protected:
	string name = ""; // name of the league
	int num_of_players; //amount of players in the league
	vector<Player*> players; // an array of players in the league
	int num_of_seasons = 1; // counter for seasons
	vector<Season*> seasons; //stl vector for each season
	Stats* league_stats; //ptr for Stats class
	bool prev_file_exist = false; //flag for previous save data for the league
	int human_players = 0; //user's input for how many human players did he choose
public:
	League(); //constructor
	League(League& other); //CC
	~League(); //destructor
	void start_league(); //start new league
	int get_num_of_seasons() { return num_of_seasons; }; //get num of seasons
	void set_season_idx(int num) { num_of_seasons = num; }; // set season index
	void set_num_of_players(int num) { num_of_players = num; }; // set num of players
	int get_num_of_players() { return num_of_players; }; //get num of players
	void save_db(); //save database
	void save_player_db(); //save player database
	void save_league_db(); //save league database
	void load_db(); //load data base
	void load_players(); // load player database
	void load_league(); //load league database
	void create_players(); //create new players
	void create_dealer(); //create new dealer
	void create_humans(int idx); //create new humans
	void create_bots(int idx); //create new bots
	void check_exist_db(const string filename);	//validate for db existence
	void on_maintenance();	//check if the file is not damaged
	void player_selection(); //player selection
	void set_human_players(int idx) { human_players = idx; }; //create new human players
	void set_num_of_seasons(int idx) { num_of_seasons = idx; }; //set number of seasons
	int choose_num_of_human_players(int idx); // choose a number of human players in game
	void suggest_previous_db(); //suggest previous save file
	bool compare_balance(Player* a, Player* b); //compare between two player's balance
	void start(); //start league
	friend ostream& operator<<(ostream& os, League& l);






};
#endif
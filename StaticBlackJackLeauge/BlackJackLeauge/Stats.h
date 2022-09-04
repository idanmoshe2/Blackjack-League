#ifndef STATS_H
#define STATS_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Card;
class Player;
class Stats
{
private:
	unsigned int wins = 0; // counter for player's wins
	unsigned int loses = 0; // counter for player's loses
	unsigned int num_of_bjs = 0; // counter for player's blackjacks
	unsigned int bust = 0; //how many times did the player got score of cards over 21
	unsigned int ties = 0; // counter for player's ties
	double highest_balance = 0; // highest balance value the player holded in the league
	double lowest_balance = 100; // lowest balance value the player holded in the league
	unsigned int num_of_hands_played; //counter for how many hands this player participated

public:
	Stats(unsigned int wins, unsigned int loses, unsigned int num_of_bjs, unsigned int bust, double highest_balance, double lowest_balance, unsigned int ties);//ctor
	void incrs_num_of_hands_played() { num_of_hands_played = num_of_hands_played + 1; };//increase number of hands played
	void incrs_wins() { wins = wins + 1; };//increase wins
	void incrs_loses() { loses = loses + 1; }; //increase loses
	void incrs_num_of_bjs() { num_of_bjs = num_of_bjs + 1; };//increase num of blackjacks
	void incrs_ties() { ties = ties + 1; }; // increas ties
	void incrs_bust() { bust = bust + 1; }; //increase bust
	void set_highest_balance(double num) { highest_balance = num; }; //set highest balance
	void set_lowest_balance(double num) { lowest_balance = num; }; //set lowest balance
	unsigned int get_wins(){ return wins; }; //get wins
	unsigned int get_loses() { return loses; }; //get loses
	unsigned int get_num_of_bjs() { return num_of_bjs; }; //get num of blackjacks
	unsigned int get_busts() { return bust; }; //get busts
	unsigned int get_ties() { return ties; }; //get ties
	unsigned int get_num_of_hands_played() { return num_of_hands_played; }; //get num of hands played
	void set_num_of_hands_played(unsigned int num) { num_of_hands_played = num; }; //set num of hands played
	double get_highest_balance() { return highest_balance; }; // get highest balance
	double get_lowest_balance() { return lowest_balance; }; //get lowest balance
	void set_wins(int idx) { wins = idx; }; // set wins
	void set_num_of_bjs(int idx) { num_of_bjs = idx; }; // set num of blackjacks
	void set_loses(int idx) { loses = idx; }; //set loses
	void set_ties(int idx) { ties = idx; }; //set ties
	void set_bust(int idx) { bust = idx; }; //set busts
	void check_highest_balance(double num); //update highest balance if needed
	void check_lowest_balance(double num); //update lowest balance if needed
	friend ostream& operator<<(ostream& os, const Stats& s); //operator overload


};

#endif
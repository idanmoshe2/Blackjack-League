#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>
using namespace std;


class Card
{

protected:
	int value; // value of the card
	string symbol; // card's shape
	int digit; // idx number of the card


public:
	Card(int digit = 0, const string symbol = "");  //ctor
	Card(Card& other);  //CC
	~Card();	//virtual dector
	int get_value() { return value; }; //get value
	int get_digit() { return digit; }; //get digit
	const string get_symbol() { return symbol; }; //get symbol
	void print_card(); //print card
	friend ostream& operator<<(ostream& os, const Card& c); //operator overload

};
#endif
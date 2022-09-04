#ifndef DECK_H
#define DECK_H
#include <stack>
#include "Card.h"
#include "League.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#define NUM_OF_CARDS 52
#define NUM_OF_PACKS 6
using namespace std;
class Card;
class League;

class Deck 
{

private:
	stack<Card*> card_deck; //stack of pointers for Card class
	League* league; // ptr for League class

public:
	Deck(); //ctor
	~Deck(); //detor
	Card* draw_card(); //draw card
	void print_deck(); //print deck
	friend ostream& operator<<(ostream& os, const Deck& d); //operator overload



};
#endif
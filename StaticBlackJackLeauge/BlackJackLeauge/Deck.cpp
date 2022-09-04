#include "Deck.h"


Deck::Deck() : league(league)
{
	int k = 0;
	array<Card*, NUM_OF_CARDS * NUM_OF_PACKS> cards_arr;
	array<string,4> symbols = { "Heart", "Diamond", "Spade", "Club" };
	for (int z = 0; z < NUM_OF_PACKS; z++)
	{
		for (unsigned int i = 0; i < symbols.size(); i++)
		{
			for (int j = 1; j <= 13; j++)
			{
				try
				{
					cards_arr[k] = new Card(j, symbols[i]);
				}
				catch (std::bad_alloc& e)
				{
					cout << e.what() << endl;
					return;
				}
				if (!cards_arr[k])
					return;
				k++;
			}
		}
	}
	random_shuffle(&cards_arr[0], &cards_arr[NUM_OF_CARDS * NUM_OF_PACKS -1]);
	for (int i = 0; i < NUM_OF_CARDS * NUM_OF_PACKS; i++)
	{
		try
		{
			card_deck.push(cards_arr[i]);
		}
		catch (std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return;
		}
		if (card_deck.empty())
			return;
		
	}
}


ostream& operator<<(ostream& os, const Deck& d)
{
	os << d.league;
	return os;
}

void Deck::print_deck()
{
	for (int i = 0; i < NUM_OF_CARDS; i++)
	{
		card_deck.top()->print_card();
		delete card_deck.top();

		card_deck.pop();
	}
}



Deck::~Deck()
{
	while (!card_deck.empty())
	{
		delete card_deck.top();
		card_deck.pop();
	}
	if (league)
		delete league;
	
}

Card* Deck::draw_card()
{
	Card* c = this->card_deck.top();
	this->card_deck.pop();
	return c;
}
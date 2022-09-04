#include "Round.h"

Round::Round(int round_num, vector<Player*> players, int num_of_players) : round_num(round_num), players(players), num_of_players(num_of_players), game(game), round_stats(round_stats) {};

Round::Round(Round& other) : round_num(other.round_num), players(other.players), num_of_players(other.num_of_players), game(other.game), round_stats(other.round_stats) {}
Round::~Round()
{

	if (game != nullptr)
		delete game;
	if (round_stats != nullptr)
		delete round_stats;
}



void Round::start_round()
{
	players[0]->reset_balance(0);
	for (int i = 1; i < num_of_players; i++)
		players[i]->reset_balance(INITIAL_ROUND_BALANCE);
	cout << "*************************Round*" << ++round_num << "*************************" << endl;
	try
	{
		game = new Game(players, num_of_players);
	}
	catch (std::bad_alloc& e)
	{
		cout << e.what() << endl;
		return;
	}
	if (!game)
		return;

	game->start_game();
	for (int i = 0; i < num_of_players; i++)
	{
		players[i]->set_season_balance(players[i]->get_round_balance());
	}
}

ostream& operator<<(ostream& os, const Round& r)
{
	os << r.game;
	return os;
}

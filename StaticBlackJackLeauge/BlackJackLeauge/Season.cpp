#include "Season.h"

Season::Season(int season_num, vector<Player*> players, int num_of_players) : season_num(season_num), players(players), num_of_players(num_of_players), season_stats(season_stats), current_round_idx(current_round_idx) {}
Season::Season(Season& other) : season_num(other.season_num), players(other.players), num_of_players(other.num_of_players), season_stats(other.season_stats), current_round_idx(other.current_round_idx) {}
;

ostream& operator<<(ostream& os, const Season& s)
{
	os << s.season_num;
	return os;
}

void Season::start_season()
{
	cout << "*************************Season*" << season_num << "*************************" << endl;
	for (auto it = players.begin(); it != players.end(); it++)
	{
		(*it)->reset_season_balance(0);
	}
	for (current_round_idx = 0; current_round_idx < num_of_rounds; current_round_idx++)
	{
		try
		{
			rounds.push_back(new Round(current_round_idx, players, num_of_players));
		}
		catch (std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return;
		}
		if (rounds.empty())
			return;
		
		rounds[current_round_idx]->start_round();
		for (int i = 0; i < num_of_players; i++)
		{
			players[i]->set_league_balance(players[i]->get_season_balance());
		}
		cout << "*************************End*of*Round*" << current_round_idx + 1 << "*************************" << endl << endl;

	}
	cout << "*************************End*of*Season*" << season_num << "*************************" << endl;
}

Season::~Season()
{
	for (auto it = rounds.begin(); it != rounds.end(); it++)
		delete (*it);
	if (rounds.size() > 0)
	{
		rounds.clear();
	}
	if (season_stats != nullptr)
		delete season_stats;

}

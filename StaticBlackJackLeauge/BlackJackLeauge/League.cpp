#define _CRT_SECURE_NO_WARNINGS
#include "League.h"
using namespace std;
#include <string.h>
#include <iostream>

League::League() : name(name), league_stats(league_stats), num_of_players(num_of_players) {
	start();
}



League::League(League& other) :
	name(other.name), num_of_players(other.num_of_players), players(other.players), seasons(other.seasons),
	num_of_seasons(other.num_of_seasons), league_stats(other.league_stats) {}

void League::start()
{
	name = "*Blackjack League*";

	check_exist_db("League_DB.csv");
	check_exist_db("Player_DB.csv");
	if (prev_file_exist)
	{
		suggest_previous_db();

	}
	else
		create_players();
	start_league();
	cout << "number of human played in this league: " << players[num_of_players - 1]->get_human_cnt() << " Humans." << endl;
}
void League::start_league()
{
	cout << "*************************League*" << name << "*************************" << endl;

	while(1)
	{
		Season* curr_season = nullptr;
		try
		{
			curr_season = new Season(num_of_seasons, players, num_of_players);
			curr_season->set_num_of_rounds(NUM_OF_ROUNDS);
		}
		catch (std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return;
		}
		if (!curr_season)
			return;

		curr_season->start_season();
		seasons.push_back(curr_season);
		save_db();


		cout << "Would you like to play another season? " << endl;
		cout << "1. Yes." << endl;
		cout << "2. No." << endl;
		int temp = players[num_of_players - 1]->choose_a_play(2);
		cout << players[num_of_players - 1]->get_name() << " chose ";
		if (temp == 1)
		{
			cout << "Yes." << endl;
			num_of_seasons++;
		}
		else
		{
			cout << "No." << endl;
			break;
		}
	}


}
bool League::compare_balance(Player* a, Player* b)
{
	return a->get_league_balance() < b->get_league_balance();
}


void League::save_player_db()
{
	ofstream db;
	db.open("Player_DB.csv");
	if (db.is_open())
	{
		db << "NAME" << "," << "TYPE" << "," << "SEASON BALANCE" << "," << "LEAGUE BALANCE";
		db << "," << "NUMBER OF WINS" << "," << "NUMBER OF BLACKJACKS" << "," << "NUMBER OF LOSES" << "," << "NUMBER OF TIES" << "," << "NUMBER OF BUSTS";
		db << "," << "HIGHEST BALANCE" << "," << "NUMBER OF HANDS PLAYED" << "\n";
		for (auto it = players.begin(); it != players.end(); ++it)
		{
			db << (*it)->get_name() << "," << (*it)->get_type() << "," << (*it)->get_season_balance();
			db << "," << (*it)->get_league_balance() << "," << (*it)->get_player_stats()->get_wins() << "," << (*it)->get_player_stats()->get_num_of_bjs() << "," << (*it)->get_player_stats()->get_loses();
			db << "," << (*it)->get_player_stats()->get_ties() << "," << (*it)->get_player_stats()->get_busts();
			db << "," << (*it)->get_player_stats()->get_highest_balance() << ",";
			db << (*it)->get_player_stats()->get_wins() + (*it)->get_player_stats()->get_loses() + (*it)->get_player_stats()->get_ties() + (*it)->get_player_stats()->get_busts() << "\n";

		}

	}
}
void League::suggest_previous_db()
{
	cout << "Previous save file found. would you like to continue or start new game?" << endl;
	cout << "0. Start new game." << endl;
	cout << "1. Continue from last save." << endl;
	int temp = choose_num_of_human_players(1);
	if (temp)
		load_db();
	else
		create_players();

}
void League::save_league_db()
{
	ofstream db;
	db.open("League_DB.csv");
	if (db.is_open())
	{
		db << "SEASON IDX" << "," << "ROUND IDX" << "\n";
		db << get_num_of_seasons() << "," << seasons.back()->get_round_idx() << "\n";

	}
}


void League::save_db()
{
	save_player_db();
	save_league_db();



}

void League::create_players()
{
	player_selection();
	int bots, humans;
	bots = MAX_PARTICIPANTS - human_players;
	set_num_of_players(bots + human_players + 1);
	create_dealer();
	create_bots(bots);
	create_humans(bots + 1);



}

void League::load_players()
{
	int pnum = 0;
	bool flag = true;
	fstream fin;
	fin.open("Player_DB.csv");
	if (fin.is_open())
	{

		vector<string> row; //Read the Data from the file as String Vector
		string line(""), word;
		while (getline(fin, line)) //Gets lines from file
		{
			if (flag)
			{
				flag = false;
				continue;

			}
			row.clear();

			stringstream s(line); //used for breaking lines
			while (getline(s, word, ',')) //read every column data of a row and store it in a string variable 'word'
			{

				row.push_back(word); //add coloumn data of a row to a vector
			}
			Player* ptr = nullptr;
			try
			{
				if (row[1] == "D")
					ptr = new Bot_Player(row[0], row[1][0]);
				else if (row[1] == "B")
					ptr = new Bot_Player(row[0], row[1][0]);
				else if (row[1] == "H")
					ptr = new Human_Player(row[0], row[1][0]);	//allocated memory for player, row[1][0] is char
			}
			catch (std::bad_alloc& e)
			{
				cout << e.what() << endl;
				fin.close();
				return;
			}
			if (!ptr)
				return;


			ptr->set_season_balance(stod(row[SEASON_BALANCE]));
			ptr->set_league_balance(stod(row[LEAGUE_BALANCE]));
			ptr->get_player_stats()->set_wins(stoi(row[NUMBER_OF_WINS]));
			ptr->get_player_stats()->set_num_of_bjs(stoi(row[NUMBER_OF_BLACKJACKS]));
			ptr->get_player_stats()->set_loses(stoi(row[NUMBER_OF_LOSES]));
			ptr->get_player_stats()->set_ties(stoi(row[NUMBER_OF_TIES]));
			ptr->get_player_stats()->set_bust(stoi(row[NUMBER_OF_BUSTS]));
			ptr->get_player_stats()->set_highest_balance(stoi(row[HIGHTEST_BALANCE]));


			pnum++;
			players.push_back(ptr);
		}
		fin.close();
		set_num_of_players(pnum);

	}

}
void League::load_db()
{
	load_players();
	load_league();
	
}

void League::load_league()
{
	bool flag = true;
	fstream fin;
	fin.open("League_DB.csv");
	if (fin.is_open())
	{

		vector<string> row; //Read the Data from the file as String Vector
		string line(""), word;
		while (getline(fin, line)) //Gets lines from file
		{
			if (flag)
			{
				flag = false;
				continue;

			}
			row.clear();

			stringstream s(line); //used for breaking lines
			while (getline(s, word, ',')) //read every column data of a row and store it in a string variable 'word'
			{

				row.push_back(word); //add coloumn data of a row to a vector
			}
			set_num_of_seasons(stoi(row[0]) + 1);
			Season* ptr = nullptr;
			try
			{
				ptr = new Season(num_of_seasons, players, num_of_players);
			}
			catch (std::bad_alloc& e)
			{
				cout << e.what() << endl;
				fin.close();
				return;
			}
			if (!ptr)
				return;
			
			ptr->set_round_idx(stoi(row[ROUND_IDX]));
			seasons.push_back(ptr);
		}
		fin.close();
	}
}




ostream& operator<<(ostream& os, League& l)
{
	l.start();
	return os;
}


void League::create_humans(int idx)
{
	string h_char_name;
	for (int i = idx; i < num_of_players; i++)
	{
		string human_name("Human ");
		string human_idx(std::to_string(i - idx + 1));
		h_char_name = human_name.append(human_idx);
		try
		{
			players.push_back(new Human_Player(h_char_name, 'H'));
		}
		catch (std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return;
		}
		if (players.empty())
			return;
	}
}

void League::create_bots(int idx)
{
	string b_char_name;
	for (int i = 1; i <= idx; i++)
	{
		string bot_name("Bot ");
		string bot_idx(std::to_string(i));
		b_char_name = bot_name.append(bot_idx);
		try
		{
			players.push_back(new Bot_Player(b_char_name, 'B'));
		}
		catch (std::bad_alloc& e)
		{
			cout << e.what() << endl;
			return;
		}
		if (players.empty())
			return;
	}
}

void League::check_exist_db(const string filename)
{
	ifstream check;
	check.open(filename);
	if (check.is_open())	//check if file exists
	{
		prev_file_exist = true;
		if (check.peek() == EOF) //checks if db file is empty
			on_maintenance();
		
		check.close();
		return;
	}
	else //if not exists creates new file
	{
		prev_file_exist = false;
		ofstream newfile;
		newfile.open(filename);
		newfile.close();
		on_maintenance();
	}
}

void League::on_maintenance()
{
	if (!prev_file_exist)
		cout << "There is no gaming history, starting a new game." << endl;
	prev_file_exist = false;	//if one of DB file is missing -> system on maintenance
}

int League::choose_num_of_human_players(int idx)
{
	unsigned int action = 0;
	do
	{
		cin >> action;
		if (action < 0 || action > idx)
			cout << "bad input." << endl << "input must be between 0 to " << idx << ". try again: ";
	} while (action<0 || action>idx);
	return action;
}

void League::player_selection()
{
	cout << "Choose between 0 to 7 human players (the rest will be played by bots): " << endl;
	int temp = choose_num_of_human_players(MAX_PARTICIPANTS);
	set_human_players(temp);
}



void League::create_dealer()
{
	try
	{
		players.push_back(new Dealer("Dealer", 'D'));
	}
	catch (std::bad_alloc& e)
	{
		cout << e.what() << endl;
		return;
	}
	if (players.empty())
		return;
}



League::~League()
{

	for (auto it = players.begin(); it != players.end(); it++)
		delete (*it);
	if (league_stats != nullptr)
		delete league_stats;

	for (auto it = seasons.begin(); it != seasons.end(); it++)
	{
		delete (*it);
	}





}




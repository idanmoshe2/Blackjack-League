#include "Game.h"

using namespace std;
Game::Game(vector<Player*> players, int num_of_players) : players(players), num_of_players(num_of_players), deck(deck), card(card)
{

}

Game::~Game()
{
	if (deck)
		delete deck;
}
void Game::user_bet()
{
	for (unsigned int i = 0; i < active_players.size(); i++)
	{
		double bet_temp = 0;
		cout << players[active_players[i]]->get_name() << ", insert bet size: ";
		bet_temp = players[active_players[i]]->choose_a_play(players[active_players[i]]->get_round_balance());
		players[active_players[i]]->set_bet(bet_temp);
		players[active_players[i]]->set_round_balance(-1 * bet_temp);
		cout << players[active_players[i]]->get_name() << " is betting on " << bet_temp << "$" << endl;
	}
}

void Game::start_game()
{
	for (int i = 0; i < limit_of_hands; i++)
	{
		reset_active_players();
		check_who_plays();
		players[0]->get_player_stats()->incrs_num_of_hands_played();
		for (int i = 0; i < active_players.size(); i++)
			players[active_players[i]]->get_player_stats()->incrs_num_of_hands_played();
		if (active_players.size() > 1)
		{
			cout << "*************************Hand*" << i + 1 << "*************************" << endl;
			user_bet();
			reset_deck();
			draw_first_two_cards();
			pre_game_print();
			gameplay();
			print_game_summary();
			check_who_plays();
			cout << endl << "*************************End*of*hand*" << current_hand_idx << "************************." << endl << endl;
			reset_game();
		}
	}
	current_hand_idx = 0;


}


void Game::draw_first_two_cards()
{
	for (int j = 0; j < 2; j++) // drwaing all prticipants hands 
	{
		for (unsigned int i = 0; i < active_players.size(); i++)//all participants first card (dealer gets last)
		{
			players[active_players[i]]->insert_card(deck->draw_card());
		}
		players[0]->insert_card(deck->draw_card());
	}
}

void Game::pre_game_print() // also checks for player Blackjack
{
	for (unsigned int i = 0; i < active_players.size(); i++)
	{
		players[active_players[i]]->check_if_bj();
		cout << players[active_players[i]]->get_name() << " hand is: ";
		players[active_players[i]]->print_current_hand();
		if (players[active_players[i]]->get_blackjack_flag())
			cout << "(Blackjack)" << endl;
		cout << "bet amount is: " << players[active_players[i]]->get_bet() << "$" << endl;
	}
	cout << players[0]->get_name() << " hand is: " << "[ ";
	players[0]->print_single_hand_card(0);
	cout << " , HIDDEN ]" << endl;
	players[0]->check_if_bj();
	cout << endl << endl;
}

void Game::dealer_has_blackjack()
{
	cout << "Dealer got Blackjack." << endl;
	players[0]->print_current_hand();
	for (unsigned int j = 0; j < active_players.size(); j++)
	{
		if (!players[active_players[j]]->get_blackjack_flag())
			continue;
		else
			players[active_players[j]]->set_tie_flag(true);

	}
}

void Game::player_turn()
{
	for (unsigned int turn = 0; turn < active_players.size();) {
		if (players[active_players[turn]]->get_blackjack_flag())
		{
			players[active_players[turn]]->set_win_flag(true);
			turn++;
			cout << endl << endl;
			continue;
		}
		cout << "Its " << players[active_players[turn]]->get_name() << "'s turn." << endl;
		int move = 0;
		cout << "Choose an option - Hit or Stand:" << endl;
		cout << "1. Hit" << endl;
		cout << "2. Stand" << endl;
		move = players[active_players[turn]]->choose_a_play(2);
		cout << players[active_players[turn]]->get_name() << " chose ";
		if (move == 1)
			cout << "Hit." << endl;
		if (move == 2)
		{
			cout << "Stand, his hand is: ";
			players[active_players[turn]]->print_current_hand();
			cout << "(sum card = " << players[active_players[turn]]->get_sum_card() << ")" << endl;
		}

		if (move == 2)
		{
			turn++;
			cout << endl << endl;
			continue;
		}
		else if (move == 1)
		{
			players[active_players[turn]]->insert_card(deck->draw_card());
			players[active_players[turn]]->print_current_hand();
			players[active_players[turn]]->update_sum_card();
			cout << players[active_players[turn]]->get_name() << "'s sum card is: " << players[active_players[turn]]->get_sum_card() << endl;
			if (players[active_players[turn]]->get_sum_card() > BLACKJACK)
			{

				cout << players[active_players[turn]]->get_name() << " busted." << endl;
				players[active_players[turn]]->set_bust_flag(true);
				turn++;
			}
		}
	}


}

void Game::dealer_turn()
{

	cout << "Its " << players[0]->get_name() << "'s turn." << endl;
	players[0]->print_current_hand();
	players[0]->update_sum_card();
	cout << "Dealer has " << players[0]->get_sum_card() << endl;

	while (players[0]->get_sum_card() < DEALER_MIN)
	{
		players[0]->insert_card(deck->draw_card());
		players[0]->print_current_hand();
		players[0]->update_sum_card();
		cout << "Dealer has " << players[0]->get_sum_card() << endl;

		if (players[0]->get_sum_card() > BLACKJACK)
		{
			cout << players[0]->get_name() << " busted." << endl;
			players[0]->set_bust_flag(true);
			for (unsigned int i = 0; i < active_players.size(); i++)
			{
				if (players[active_players[i]]->get_bust_flag())
					continue;
				else
					players[active_players[i]]->set_win_flag(true);
			}
		}
		if (players[0]->get_sum_card() <= BLACKJACK && players[0]->get_sum_card() >= DEALER_MIN)
		{
			for (unsigned int i = 0; i < active_players.size(); i++)
			{
				if (players[active_players[i]]->get_bust_flag())
					continue;
				
				else
				{
					if (players[active_players[i]]->get_sum_card() > players[0]->get_sum_card())
					{
						players[active_players[i]]->set_win_flag(true);
						house_win_flag = false;

					}
					if (players[active_players[i]]->get_sum_card() == players[0]->get_sum_card())
					{
						players[active_players[i]]->set_tie_flag(true);
						house_win_flag = false;

					}
				}
			}
		}
	}
}

void Game::print_game_summary()
{
	cout << "*************************Hand*" << ++current_hand_idx << "*summary:*************************" << endl;
		for (unsigned int i = 0; i < active_players.size(); i++)
		{
				if (!(players[active_players[i]]->get_tie_flag()) && !(players[active_players[i]]->get_blackjack_flag()) && players[active_players[i]]->get_win_flag())
				{
					house_win_flag = false;
					cout << players[active_players[i]]->get_name() << " win, ";
					prize = 2 * players[active_players[i]]->get_bet();
					cout << players[active_players[i]]->get_name() << " earned " << prize - players[active_players[i]]->get_bet() << "$" << endl;
					players[active_players[i]]->set_round_balance(prize);
					players[active_players[i]]->get_player_stats()->check_highest_balance(players[active_players[i]]->get_round_balance());//check if highest balance need to be updated
					players[active_players[i]]->get_player_stats()->incrs_wins();
					house_win_flag = false;
				}
				else if (!(players[active_players[i]]->get_tie_flag()) && players[active_players[i]]->get_blackjack_flag() && players[active_players[i]]->get_win_flag())
				{
					cout << players[active_players[i]]->get_name() << " win with Blackjack, ";
					prize = players[active_players[i]]->get_bet() + players[active_players[i]]->get_bet() * 1.5;
					cout << players[active_players[i]]->get_name() << " earned " << prize - players[active_players[i]]->get_bet() << "$" << endl;
					players[active_players[i]]->set_round_balance(prize);
					players[active_players[i]]->get_player_stats()->check_highest_balance(players[active_players[i]]->get_round_balance());//check if highest balance need to be updated
					players[active_players[i]]->get_player_stats()->incrs_wins();
					players[active_players[i]]->get_player_stats()->incrs_num_of_bjs();
					house_win_flag = false;

				}
				else if (players[active_players[i]]->get_tie_flag() && !(players[active_players[i]]->get_win_flag()))
				{
					cout << players[active_players[i]]->get_name() << " got a tie with the Dealer, ";
					prize = players[active_players[i]]->get_bet();
					cout << players[active_players[i]]->get_name() << " earned his bet back: " << prize << "$" << endl;
					players[active_players[i]]->set_round_balance(prize);
					players[active_players[i]]->get_player_stats()->check_highest_balance(players[active_players[i]]->get_round_balance());//check if highest balance need to be updated
					players[active_players[i]]->get_player_stats()->incrs_ties();

				}
				else if (players[active_players[i]]->get_bust_flag())
				{
					cout << players[active_players[i]]->get_name() << " busted." << endl;
					players[active_players[i]]->get_player_stats()->incrs_bust();
					pay_to_dealer(players[active_players[i]]);
					players[active_players[i]]->get_player_stats()->check_lowest_balance(players[active_players[i]]->get_round_balance());//check if lowest balance need to be updated

				}
				else
				{
					cout << players[active_players[i]]->get_name() << " lose." << endl;
					players[active_players[i]]->get_player_stats()->incrs_loses();
					pay_to_dealer(players[active_players[i]]);
					players[active_players[i]]->get_player_stats()->check_lowest_balance(players[active_players[i]]->get_round_balance());//check if lowest balance need to be updated

				}

		}

		if (house_win_flag)
		{
			cout << "House wins." << endl;
			players[0]->get_player_stats()->incrs_wins();

		}
		players[0]->get_player_stats()->check_highest_balance(players[0]->get_round_balance());//check if dealer's highest balance need to be updated


}

void Game::reset_game()
{
	house_win_flag = true;
	reset_deck();
	prize = -1;
	for (int i = 0; i < num_of_players; i++)
	{
		players[i]->delete_cards();
		players[i]->set_tie_flag(false);
		players[i]->set_win_flag(false);
		players[i]->set_blackjack_flag(false);
		players[i]->set_bust_flag(false);
		players[i]->set_bet(0);
	}
}

void Game::gameplay()
{
	if (players[0]->get_blackjack_flag())
		dealer_has_blackjack();
	else
	{
		player_turn();
		dealer_turn();
	}
	cout << endl;
}

void Game::check_who_plays()
{
	for (int i = 1; i < num_of_players; i++)
	{
		if (players[i]->get_round_balance() >= 1)
		{
			if (std::find(active_players.begin(), active_players.end(), i) == active_players.end())
				active_players.push_back(i);
		}
		else
		{
			cout << players[i]->get_name() << " lost all his money." << endl;
			auto it = std::find(active_players.begin(), active_players.end(), i);
			if (it != active_players.end())
				active_players.erase(it);
			
		}
	}
}

void Game::reset_active_players()
{
	if (active_players.size() > 0)
		active_players.clear();
}

void Game::reset_deck()
{
	if (deck != nullptr)
		delete deck;
	try
	{
		deck = new Deck();
	}
	catch (std::bad_alloc& e)
	{
		cout << e.what() << endl;
		return;
	}
	if (!deck)
		return;
	

}

void Game::pay_to_dealer(Player* p)
{
	players[0]->set_round_balance(p->get_bet());
}



ostream& operator<<(ostream& os, const Game& g)
{
	os << g.card;
	return os;
}



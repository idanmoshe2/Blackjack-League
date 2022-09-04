// BlackJackLeagueClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "League.h"
#include <time.h>
#define   _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <conio.h> // for getch
#include <stdlib.h> // for exit

using namespace std;

void WaitForUserPressKey()
{
	printf("Press any key to exit");
	_getch();
}

void Start_new_league()
{
	League league;
}

int main()
{
	srand(time(NULL));
	Start_new_league();
	cout << "LEAKS: " << _CrtDumpMemoryLeaks() << endl;
	WaitForUserPressKey();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

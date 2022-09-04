#include "Card.h"
#include "Deck.h"
#include "League.h"
#include <time.h>
#include <iostream>
#define   _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <conio.h> // for getch
#include <stdlib.h> // for exit

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_
#define new ( NORMAL_BLOCK , __FILE_ , _LINE_ )
#define new DBG_NEW
#endif
#endif

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







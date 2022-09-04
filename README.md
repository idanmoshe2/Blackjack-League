# blackjack-league

Program capabilities:

	- Activation of the 7 player blackjack league + dealer.
	- Activating a blackjack league with 7 players + dealer.
	- Allowing to choose between a human players and a bot players.
	- Capable to load the league and continuing from the last game point.
	- Capable to load a game from a database.
	- Collecting a league game statistics for each human/bot player.
	- Printing the game views and player data while running.
	- Capable to stop the sequence of games at the end of each season or continue for another season.

User Interface:

	- Start a new league or load a saved data of occuring league.
	- Choose amount of human players (the rest will be played by bots).
	- Choose amount of bet for each round.
	- Choose the next move for each human player (hit or stand).
	- End game and save data or continue to another season.
Classes:

	-League: Managing the league, this class is the top level.
	-Season: Saving data for each season, managing seasons and activating Round class.
	-Round: Saving data for each round, managing rounds and activating Game class.
	-Game: Managing each game and updating data for each class
	-Player: Managing features for each player.
	-Stats: Managing statistics for each player in each game and saving league data for database.
	
UML Diagram is attached to this folder. ("UMLDiagram.png")

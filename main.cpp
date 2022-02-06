#include "gameEngine.h"
#include <iostream>
using namespace std;

void handleGame(string input){
	Level l =readLevelInfo(readFile(input));
	try {
		Game game;
		game.currentLevel = l;
		startGame (game);
	}
	catch (EndGameException ex)	
	{
		handleGame(input);
	}
}

int main(int argc, char const *argv[])
{
	
	
	handleGame(argv[1]);

	return 0;
}
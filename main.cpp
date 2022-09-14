// TowerHannoiGame.cpp : Defines the entry point for the console application.
//

#include "TowersOfHanoiGame.cpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main(){
	std::cout << "\033[2J\033[1;1H";

	int discCount = 4;
	int stackCount = 3;

	TowersOfHanoiGame game = TowersOfHanoiGame(stackCount, discCount);

	bool wonGame = false;

	std::cout << std::endl;
	while (wonGame == false){

		game.PrintTowers();
		
		int from;
		
		std::cout << "Stack to move from: ";
		std::cin >> from;
		
		std::cout << "\r";

		int to;
		
		std::cout << "Stack to move to: ";
		std::cin >> to;

		MoveResult result = game.MoveDisc(from, to);

		std::cout << "\033[2J\033[1;1H";
		
		switch(result){

			case MoveResult::VALID_MOVE:
				std::cout << "Moved from " << from << " to " << to << std::endl;
				break;

			case MoveResult::EMPTY_STACK:
				std::cout << "Cannot move a ring from an empty stack" << std::endl;
				break;

			case MoveResult::INVALID_MOVE:
				std::cout << "Cannot place a ring on top of a smaller ring" << std::endl;
				break;

			case MoveResult::INVALID_STACK:
				std::cout << from << " or " << to << " is not a valid stack." << std::endl;
				break;

			default:
				break;
			
		}

		// Check for win
		wonGame = game.CheckWin();

	}

	std::cout << "\033[2J\033[1;1H";
	
	std::cout << std::endl;
	game.SaveToFile("moves.txt");

	game.PrintTowers();
	game.PrintWinString();

	//ArrayBasedQueue moves = game.GetMoves();

	
	
};
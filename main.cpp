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
		
		std::string line;

		std::cout << "Stack to move from and to (Format like: '1 3'): ";
		getline(cin, line);

		if (line == "-1"){
			break;
		}

		std::vector<std::string> output;
		std::string::size_type prev_pos = 0, pos = 0;

		while((pos = line.find(" ", pos)) != std::string::npos){
			std::string substring(line.substr(prev_pos, pos - prev_pos));
			output.push_back(substring);
			prev_pos = ++pos;
		}
		output.push_back(line.substr(prev_pos, pos - prev_pos));
		
		std::cout << "\033[2J\033[1;1H";

		if (output.size() != 2){
			std::cout << "Invalid input received" << std::endl;
		} else {

			std::cout << "\r";

			int from = atoi(output[0].c_str());
			int to = atoi(output[1].c_str());

			MoveResult result = game.MoveDisc(from, to);
			
			switch(result){

				case MoveResult::VALID_MOVE:
					std::cout << "Moved from " << from << " to " << to << std::endl;
					break;

				case MoveResult::EMPTY_STACK:
					std::cout << "Cannot move a ring from an empty stack." << std::endl;
					break;

				case MoveResult::INVALID_MOVE:
					std::cout << "Cannot place a ring on top of a smaller ring." << std::endl;
					break;

				case MoveResult::INVALID_STACK:
					std::cout << from << " or " << to << " is not a valid stack." << std::endl;
					break;
				case MoveResult::SAME_STACK:
					std::cout << "Cannot move a ring to a stack it is already in." << std::endl;
					break;

				default:
					break;
				
			}

			// Check for win
			wonGame = game.CheckWin();
		}

	}

	std::cout << "\033[2J\033[1;1H";
	std::cout << std::endl;
	game.SaveToFile("moves.txt");
	game.PrintTowers();

	if(wonGame){
		game.PrintWinString();
	}
	else {
		game.PrintLoseString();
	}

	//ArrayBasedQueue moves = game.GetMoves();

	
	
};
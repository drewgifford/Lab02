#include <iostream>
#include <string>
#include <cmath>
#include "TowersOfHanoiGame.h"

// UTILITY FUNCTIONS

std::string center(std::string input, int width = 113) {

	int difference = width - input.length();
	// Center string on width
	return std::string(std::ceil(difference/2), ' ') + input + std::string(std::ceil(difference/2), ' ');
}
std::string discAsBar(int val){
	std::string str = "";
	// Return a formatted string of # based on the width of the ring
	return std::string((val*2-1), '#');

}

TowersOfHanoiGame::TowersOfHanoiGame(int count_stacks, int count_discs) : m_gameEnded(false){
    m_count_stacks = count_stacks;
    m_count_discs = count_discs;

    // Create new array of stacks
    m_stacks = new ArrayBasedStack[count_stacks];
    m_moves = ArrayBasedQueue();

    // Add each disc to the first stack
    // Top disc = 1, bottom disc = m_count_discs
    int bottomDisc = 1;
    int topDisc = m_count_discs;

    for(int i = topDisc; i >= bottomDisc; i--){
		m_stacks[0].push(i);
	}
}

MoveResult TowersOfHanoiGame::MoveDisc(int from, int to){

    // Check if the from or to stack is invalid, i.e. greater than the max amount of discs or less than 1
    if (from <= 0 || from > GetStacksCount() || to <= 0 || to > GetStacksCount()){
        return MoveResult::INVALID_STACK; // 0 is an invalid stack
    }

    // This is the same stack
    if (from == to){
        return MoveResult::SAME_STACK;
    }

    int fromIndex = from-1;
    int toIndex = to-1;

    // Create alias so we don't copy the arrays
    // We have to do this to keep our code clean when we update the arrays
    ArrayBasedStack & fromStack = m_stacks[fromIndex];
    ArrayBasedStack & toStack = m_stacks[toIndex];

    // Get the top ring of each stack. If it's empty then it returns 0
    int fromRing = GetStackTopValue(fromIndex);
    int toRing = GetStackTopValue(toIndex);

    // If the from ring is nonexistent, we can't move it.
    if (fromRing == 0){
        return MoveResult::EMPTY_STACK;
    }

    // Compare the two. If the TO from has a lower value than the FROM ring, then we can't allow that.
    if (toRing < fromRing && toRing != 0){
        return MoveResult::INVALID_MOVE;
    }

    // Move the ring
    fromStack.pop();
    toStack.push(fromRing);

    std::string moveString = std::to_string(from) + " " + std::to_string(to);
    m_moves.enQueue(moveString);

    // Since the move is valid, return that!
    return MoveResult::VALID_MOVE;
}

int TowersOfHanoiGame::GetStackTopValue(int stackIndex) {
    // Get the array at the index
    ArrayBasedStack stack = GetStack(stackIndex);

    // If the array is empty, return 0.
    // Otherwise, return the top value.
    if (stack.isEmpty()) return 0;
    return stack.peek();
}

bool TowersOfHanoiGame::CheckWin(){

    // Get the last stack
    ArrayBasedStack finalStack = GetStack(GetStacksCount()-1);

    // If there aren't the full amount of the rings in the last stack, return false
    if (finalStack.getCount() < GetStacksCount()) return false;

    // Get the array of the rings in the last stack
    int * rings = finalStack.getArray();

    // Loop through every ring, starting from the smallest to largest
    for(int i = 0; i < GetDiscsCount(); i++){
        
        int ringIndex = GetDiscsCount() - i - 1;

        // If the ring number is not in order, return false
        if (rings[ringIndex] != i+1){
            return false;
        }

    }
    // If all rings are correct, return true
    return true;


}

// i spent too much time on this :(
void TowersOfHanoiGame::PrintTowers(){

    // Get the width of each "column"
    int colWidth = (GetDiscsCount() * 2) + 3;

    // The amount of rows in the output should be the amount of discs, and room for the labels below.
    std::string * strings = new std::string[GetDiscsCount() + 2];

    // Loop through the stacks
    for (int stackIndex = 0; stackIndex < GetStacksCount(); stackIndex++){

        // Get the stack at the index, and some useful variables
        ArrayBasedStack & stack = GetStack(stackIndex);
        int stackDiscsCount = stack.getCount();
        int * stackArray = stack.getArray();
        
        // For each disc that may be present
        for(int discIndex = 1; discIndex <= GetDiscsCount(); discIndex++){

            // If there is no disc at this level, print nothing
            if (discIndex > stackDiscsCount){
                strings[discIndex] += center(" ", colWidth);
            }
            // If there is a disc at this value, print a bar to represent that disc
            else {
                strings[discIndex] += center(discAsBar(stackArray[discIndex-1]), colWidth);
            }
        }
        strings[0] += center(std::to_string(stackIndex+1), colWidth);
    }

    // Print the string array
    for(int i = m_count_discs; i >= 0; i--){
		std::cout << strings[i] << std::endl;
	}
}

void TowersOfHanoiGame::PrintWinString(){
    int colWidth = (GetDiscsCount() * 2) + 3;

    int width = colWidth * 3;

    std::string moveString = "You won in " + std::to_string(m_moves.getCount()) + " moves!";
    std::string resultsSavedString = "Results saved to moves.txt";

    std::cout << center(moveString, width) << std::endl;
    std::cout << center(resultsSavedString, width) << std::endl;
}

void TowersOfHanoiGame::SaveToFile(std::string fileName){

    ArrayBasedQueue queue = m_moves;

    // Can you write this to a file called [fileName].txt?

}


// MINOR FUNCTIONS

TowersOfHanoiGame::~TowersOfHanoiGame(){
    // Delete memory of the stacks
    m_stacks = NULL;
    delete m_stacks;
}

bool TowersOfHanoiGame::GetGameEnded() const {
    return m_gameEnded;
}

int TowersOfHanoiGame::GetDiscsCount() const {
    return m_count_discs;
}

int TowersOfHanoiGame::GetStacksCount() const {
    return m_count_stacks;
}

ArrayBasedQueue TowersOfHanoiGame::GetQueue() const {
    return m_moves;
}

ArrayBasedStack & TowersOfHanoiGame::GetStack(int index) const {
    return m_stacks[index];
}

ArrayBasedStack * TowersOfHanoiGame::GetStacks() const {
    return m_stacks;
}


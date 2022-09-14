#include <string>
#include "StackQueue.h"


enum MoveResult {
	VALID_MOVE,
	INVALID_STACK,
	EMPTY_STACK,
	INVALID_MOVE,
    SAME_STACK,
};

class TowersOfHanoiGame {
    public:
        TowersOfHanoiGame(int, int);
        virtual ~TowersOfHanoiGame();

        virtual MoveResult MoveDisc(int, int);
        virtual bool CheckWin();
        virtual void PrintWinString();
        virtual void PrintTowers();
        virtual void SaveToFile(std::string);

        virtual int GetStackTopValue(int);

        virtual bool GetGameEnded() const;
        virtual int GetStacksCount() const;
        virtual int GetDiscsCount() const;

        virtual ArrayBasedQueue GetQueue() const;
        virtual ArrayBasedStack * GetStacks() const;
        virtual ArrayBasedStack & GetStack(int) const;

        bool m_gameEnded;
        int m_count_stacks;
        int m_count_discs;
        ArrayBasedStack * m_stacks;
        ArrayBasedQueue m_moves;

    private:
};
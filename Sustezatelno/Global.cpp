#include "Global.h"

BoardState* currentBoard;
int difficulty = 1;
bool ingame = 0;

std::array<std::function<void(BoardState*&, bool)>, 1> difficultyMoves = {
   [](BoardState*& board, bool start) { AI_RandomMove(board, start); }
};
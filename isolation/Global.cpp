#include "Global.h"

Board::BoardState* currentBoard;
int difficulty = 1;
bool ingame = 0;

std::array<std::function<void(Board::BoardState*&, bool)>, 1> difficultyMoves = {
   [](Board::BoardState*& board, bool start) { Board::RandomMove(board, start); }
};
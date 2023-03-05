#pragma once
#include "BoardState.h"
#include <functional>
#include <array>

extern Board::BoardState* currentBoard;
extern int difficulty;
extern bool ingame;
extern std::array<std::function<void(Board::BoardState*&, bool)>, 1> difficultyMoves;
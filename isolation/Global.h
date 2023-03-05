#pragma once
#include "BoardState.h"
#include "DecisionMaker.h"
#include <functional>
#include <array>

extern BoardState* currentBoard;
extern int difficulty;
extern bool ingame;
extern std::array<std::function<void(BoardState*&, bool)>, 1> difficultyMoves;
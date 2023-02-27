#include "DecisionMaker.h"
#include "BoardState.h"
#include <iostream>

void AI_RandomMove(BoardState*& board, bool start) {

	std::vector<std::pair<int, int>> allMoves;
	board->GetPossibleMoves(allMoves, false);

	if (start)
	{
		int x = 0, y = 0;
		do
		{
			x = rand() % (board->getWidth() - 1);
			y = rand() % (board->getHeight() - 1);
			std::cout << x << "  " << y;
		} while (board->getPos(x, y) != 0);
		
		board->setX(x, y);
	}
	else
	{
		int move = rand() % allMoves.size();
		board->moveX(allMoves[move].first, allMoves[move].second);
	}
}



void AI_EvaluatedMove(BoardState*& board, bool start, int depth, int allowedSearch) {

}
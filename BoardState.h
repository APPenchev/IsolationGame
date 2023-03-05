#pragma once
#include "TreeNode.h"
#include <vector>


class BoardState {
	private:
		int width;
		int height;
		int x_X = 0, x_Y = 0, o_X = 0, o_Y = 0;
		int** board;
	public:
		BoardState();
		virtual ~BoardState();
		BoardState(int, int);
		BoardState(int, int, int, int, int, int);
		BoardState(BoardState&, bool, int, int);

		void fill();
		void GetPossibleBoardStates(std::vector<TreeNode<BoardState*>*>&, bool);
		void GetPossibleMoves(std::vector<std::pair<int, int>>&, bool);
		int GetPossibleMoves(bool);

		int getWidth() const;
		int getHeight() const;

		void setO(int, int);
		void setX(int, int);
		void moveO(int, int);
		void moveX(int, int);

		int getPos(int, int) const;
		void setPos(int, int, int);
};

void DisplayBoards(std::vector<TreeNode<BoardState*>*>, bool);
void DisplayBoard(BoardState*, bool, int);
void DisplayBoard(BoardState*, bool);
void DisplayBoard(BoardState*);
void DisplayBoard(BoardState*, int, int);


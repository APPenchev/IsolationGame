#pragma once
#include "GameState.h"
#include "BoardState.h"
#include "Global.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <functional>

class Selectable
{
	std::string text;
	std::function<void()> function;
	bool selectable = true;
public:
	Selectable(std::string tx, std::function<void()> func) {
		this->text = tx;
		this->function = func;
	}
	void OnClick() {
		this->function();
	}
	std::string getText() {
		return this->text;
	}
	void setText(std::string text) {
		this->text = text;
	}
	void toggle(bool toggle)
	{
		this->selectable = toggle;
	}
	bool getSelectable() { return this->selectable; }
};

class Menu : public GameState
{
private:
	int selector = 0;
	std::vector<Selectable*> options;
public:

	void Init() override {}
	void Cleanup() override {
		system("cls");
	}
	void HandleEvents() override
	{
		if (GetKeyState('S') & 0x8000)
		{
			do
			{
				selector++;
				if (selector <= -1)
					selector = options.size() - 1;
				else if (selector >= options.size())
					selector = 0;
			} while (!options[selector]->getSelectable());
			Sleep(100);
		}
		else if (GetKeyState('W') & 0x8000)
		{
			do
			{
				selector--;
				if (selector <= -1)
					selector = options.size() - 1;
				else if (selector >= options.size())
					selector = 0;
			} while (!options[selector]->getSelectable());
			Sleep(100);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			options[selector]->OnClick();
			Sleep(100);
		}
	}
	void Resume() override
	{
		Draw();
	}
	void Update() override
	{

	}
	void Draw() override
	{
		
		system("cls");
		std::cout << "\n";
		if (options.size() != 0)
		{
			for (int i = 0; i < options.size(); i++)
			{
				std::cout << "  ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (options[i]->getSelectable()) ? 15 : 8);
				if (i == selector)
				{
					std::cout << "  ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
				}
				std::cout << options[i]->getText();
				
				std::cout << std::endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}
		else std::cout << "Empty Menu!";
	}
	std::vector<Selectable*> getOptions(){
		return this->options;
	}
	Selectable* getOption(int index) {
		return this->options[index];
	}
	void addOption(Selectable* option) {
		this->options.push_back(option);
	}
};

class MainMenu : public Menu
{
	
public:
	void Init() override
	{
		Selectable* NewGame = new Selectable("New Game", [this]() {
			this->getEngine()->ChangeState("Difficulty_Menu");
		});
		Selectable* Continue = new Selectable("Continue", [this]() {
			this->getEngine()->ChangeState("Game");
		});
		
		Selectable* Tutorial = new Selectable("Tutorial", [this]() {
			this->getEngine()->ChangeState("Tutorial");

		});
		Selectable* Exit = new Selectable("Exit", [this]() {
			this->getEngine()->Quit();
		});
		addOption(NewGame);
		addOption(Continue);
		addOption(Tutorial);
		addOption(Exit);
		
		Resume();
	}
	void Resume() override
	{
		if(ingame) getOption(1)->toggle(true);
		else getOption(1)->toggle(false);
		Draw();
	}
};

class DifficultyMenu : public Menu
{

public:
	void Init() override
	{
		Selectable* Easy = new Selectable("Easy", [this]() {
			difficulty = 1;
			this->getEngine()->ChangeState("Game_Start");
		});
		Selectable* Medium = new Selectable("Medium", [this]() {
			difficulty = 2;
			this->getEngine()->ChangeState("Game_Start");
		});
		Selectable* Hard = new Selectable("Hard", [this]() {
			difficulty = 3;
			this->getEngine()->ChangeState("Game_Start");
		});
		Selectable* Extreme = new Selectable("Extreme", [this]() {
			difficulty = 4;
			this->getEngine()->ChangeState("Game_Start");
		});
		Selectable* Exit = new Selectable("Back", [this]() {

			this->getEngine()->ChangeState("Main_Menu");
		});
		addOption(Easy);
		addOption(Medium);
		addOption(Hard);
		addOption(Extreme);
		addOption(Exit);

		Resume();

	}
};

class Tutorial : public GameState
{
private:
	int step = 0;
	bool update = 0;
	BoardState* tutorialBoard;
public:
	void Init() {
		tutorialBoard = new BoardState(5, 5);
	}
	void Cleanup() {}
	void HandleEvents() {
		if (GetAsyncKeyState(VK_RETURN))
		{
			update = true;
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			this->getEngine()->ChangeState("Main_Menu");
			Sleep(200);
		}
	}
	void Resume() {
		if (step >= 10)
		{
			step = 0;
			update = false;
			delete tutorialBoard;
			tutorialBoard = new BoardState(5, 5);
		}
		Draw();
	}
	void Update() {
		if (update)
		{
			step++;
			switch (step)
			{
			case 4:
				tutorialBoard->setO(2, 2);
				break;
			case 5:
				tutorialBoard->setX(2, 1);
				break;
			case 6:
				tutorialBoard->moveO(0, 0);
				break;
			case 7:
				tutorialBoard->moveX(1, 0);
				break;
			case 8:
				tutorialBoard->moveO(0, 4);
				break;
			case 10:
				this->getEngine()->ChangeState("Main_Menu");
				break;
			}
			update = false;
		}
	}
	void Draw() {
		system("cls");
		switch (step)
		{
		case 0:
			DisplayBoard(tutorialBoard);
			std::cout << "Welcome to \nthe beautiful game of Isolation. \n(Press Enter)";
			break;
		case 1:
			DisplayBoard(tutorialBoard);
			std::cout << "This tutorial will show you\nthe rules of the game.";
			break;
		case 2:
			DisplayBoard(tutorialBoard);
			std::cout << "To begin the game player 1\nhas to select the place where he will begin from";
			break;
		case 3:
			DisplayBoard(tutorialBoard);
			std::cout << "Let's start from the centre\nwhy not";
			break;
		case 4:
			DisplayBoard(tutorialBoard);
			std::cout << "Alright, now it's player 2's turn\nHe will go above player 1";
			break;
		case 5:
			DisplayBoard(tutorialBoard,true);
			std::cout << "So now the game begins\nEach player can move\nhorisontally, vertially and diagonally\nunless they are blocked by anything in the way";
			break;
		case 6:
			DisplayBoard(tutorialBoard);
			std::cout << "When a player moves they leave behind\na nasty blockade that cannot be passed";
			break;
		case 7:
			DisplayBoard(tutorialBoard);
			std::cout << "Now players take turns";
			break;
		case 8:
			DisplayBoard(tutorialBoard);
			std::cout << "The game ends when one of the players is \nunable to move";
			break;
		case 9:
			std::cout << "\n\n\n      Well that is all there is to it\n                  Have fun!";
			break;
		}


	}
};

class Game : public GameState
{
private:
	int selected = 0;
	BoardState* gameBoard;
	bool update = false;
	bool move = false;
	std::vector<std::pair<int, int>> allOMoves;

public:
	void Init() {
		
	}
	void Cleanup() {
		system("cls");
	}
	void HandleEvents() {
		if (GetKeyState('A') & 0x8000)
		{
			selected--;
			if (selected <= -1)
				selected = allOMoves.size() - 1;
			Sleep(200);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			selected++;
			if (selected >= allOMoves.size())
				selected = 0;
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			gameBoard->moveO(allOMoves[selected].first, allOMoves[selected].second);
			update = true;
			move = true;
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			this->getEngine()->ChangeState("Main_Menu");
			Sleep(200);
		}
	}
	void Resume() {
		update = true;
	}
	void Update() {
		if (move)
		{
			if(gameBoard->GetPossibleMoves(false) != 0)
				difficultyMoves[difficulty - 1](gameBoard, false);
			else
			{
				std::cout << "\n      You Win!\n";
				system("pause");
				ingame = false;
				this->getEngine()->ChangeState("Main_Menu");
			}
			move = false;

		}
		if (update)
		{
			allOMoves.clear();
			gameBoard->GetPossibleMoves(allOMoves, true);
			if (allOMoves.size() == 0)
			{
				std::cout << "\n      Game over\n";
				system("pause");
				ingame = false;
				this->getEngine()->ChangeState("Main_Menu");
			}
			selected = 0;
			update = false;
		}
	}
	void Draw() {
		system("cls");
		DisplayBoard(gameBoard, true, selected);
		std::cout << allOMoves.size() << " " << selected << " " << allOMoves[selected].first << " " << allOMoves[selected].second;
	}
	void setBoard(BoardState* gameBoard) { this->gameBoard = gameBoard; }
};

class GameBegin : public GameState
{
private:
	int posX = 0;
	int posY = 0;
	BoardState* gameBoard;
public:
	void Init() {
		gameBoard = new BoardState(5, 5);
		posX = 0;
		posY = 0;
	}
	void Cleanup() {
		system("cls");
	}
	void HandleEvents() {
		if (GetKeyState('W') & 0x8000)
		{
			posY--;
			if (posY <= -1)
				posY = gameBoard->getHeight()-1;
			Sleep(200);
		}
		else if (GetKeyState('S') & 0x8000)
		{
			posY++;
			if (posY >= gameBoard->getHeight())
				posY = 0;
			Sleep(200);
		}
		else if (GetKeyState('A') & 0x8000)
		{
			posX--;
			if (posX <= -1)
				posX = gameBoard->getWidth() - 1;
			Sleep(200);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			posX++;
			if (posX >= gameBoard->getWidth())
				posX = 0;
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_RETURN))
		{
			ingame = true;
			gameBoard->setO(posX, posY);
			difficultyMoves[difficulty-1](gameBoard, true);
			dynamic_cast<Game*>(this->getEngine()->getGameState("Game"))->setBoard(gameBoard);
			this->getEngine()->ChangeState("Game");
			Sleep(200);
		}
		else if (GetAsyncKeyState(VK_ESCAPE))
		{
			this->getEngine()->ChangeState("Main_Menu");
			Sleep(200);
		}
	}
	void Resume() {
		Init();
	}
	void Update() {

	}
	void Draw() {
		system("cls");
		DisplayBoard(gameBoard, posX, posY);
		std::cout << "\n\nPress Enter to select location!";

	}
};
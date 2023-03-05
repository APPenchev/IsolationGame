#include <iostream>
#include <vector>
#include <time.h>
#include "BoardState.h"
#include "DecisionMaker.h"
#include "DecisionMakerX.h"
#include "GameEngine.h"
#include "GameStates.h"
#include <algorithm>
using namespace std;

int main()
{
	srand(time(0));
	GameEngine* gameEngine = new GameEngine;

	MainMenu* mainMenu = new MainMenu;
	Tutorial* tutorial = new Tutorial;
	DifficultyMenu* difficultyMenu = new DifficultyMenu;
	Game* inGame = new Game;
	GameBegin* beginGame = new GameBegin;

	gameEngine->PushState("Main_Menu",mainMenu);
	gameEngine->PushState("Tutorial",tutorial);
	gameEngine->PushState("Difficulty_Menu", difficultyMenu);
	gameEngine->PushState("Game_Start", beginGame);
	gameEngine->PushState("Game", inGame);

	gameEngine->Init();
	gameEngine->ChangeState("Main_Menu");

	while (gameEngine->Running())
	{
		Sleep(100);
		gameEngine->Run();
	}
}


#pragma once

#include <map>
#include <string>
#include "GameState.h"

class GameEngine
{
private:
	std::map<std::string,GameState*> states;
	GameState* currentState;
	bool m_running;

public:
	void Init() {
		m_running = true;
	};
	void Cleanup() {
		// Idk man idk
	};

	void ChangeState(std::string state)
	{
		std::map<std::string, GameState*>::iterator it = states.find(state);
		if (it != states.end()) {
			GameState*& obj = it->second;
			if(this->currentState != nullptr)
				this->currentState->Cleanup();
			this->currentState = obj;
			this->currentState->Resume();
		}
		else {
			// idk
		}
	};

	void PushState(std::string name, GameState* state)
	{
		state->setEngine(this);
		state->Init();
		states.insert(std::pair<std::string,GameState*>(name, state));
	};

	GameState* getCurrentGameState() { return this->currentState; }
	GameState* getGameState(std::string state)
	{
		std::map<std::string, GameState*>::iterator it = states.find(state);
		if (it != states.end())
			return it->second;
		return nullptr;
	}

	void Run()
	{
		getCurrentGameState()->HandleEvents();
		getCurrentGameState()->Update();
		getCurrentGameState()->Draw();
	}

	bool Running() { return m_running; }
	void Quit() { m_running = false; }


};
#pragma once

class GameEngine;
class GameState
{
private:
	GameEngine* ge;
public:
	void setEngine(GameEngine* ge) {
		this->ge = ge;
	}
	GameEngine* getEngine() const {
		return ge;
	}
	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void HandleEvents() = 0;
	virtual void Resume() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
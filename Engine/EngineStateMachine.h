#pragma once
#include <array>

enum EngineState
{
	Message = 0,
	NewGameObject = 1,
	Render = 2,
	DeleteObject = 3,
};


class GameState
{
private:
	std::array<EngineState, 4> states;
public:
	EngineState currentState;
	GameState();
	~GameState();
	void nextState();
	void setState(EngineState& newState);
};


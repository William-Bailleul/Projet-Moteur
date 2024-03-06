#pragma once
#include <array>

enum EngineState
{
	Message = 0,
	NewGameObject = 1,
	Render = 2,
};


class GameState
{
private:
	std::array<EngineState, 3> states;
public:
	EngineState currentState;
	GameState();
	~GameState();
	void nextState();
	void setState(EngineState& newState);
};


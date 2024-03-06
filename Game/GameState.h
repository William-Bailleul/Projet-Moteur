#pragma once
#include <array>

enum PlayState
{
	Home = 0,
	Targetting = 1,
	Shoot = 2,
	Quit = 3,
};


class GameState
{
private:
	std::array<PlayState, 4> states;
public:
	PlayState currentState;
	GameState();
	~GameState();
	void nextState();
	void setState(PlayState& newState);
};
      
 
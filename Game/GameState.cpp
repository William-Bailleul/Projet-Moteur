#include "GameState.h"

void GameState::Init() {
	states = {
	PlayState::Home,
	PlayState::Targetting,
	PlayState::Shoot,
	PlayState::Quit,
	};

	currentState = states[0];
}

void GameState::nextState() {
	currentState = states[(currentState + 1) % states.size()];
}

void GameState::setState(PlayState& newState) {
	//Before changing state 

	currentState = newState;
	// after changing statae

}

GameState::GameState() {};
GameState::~GameState() {};

 
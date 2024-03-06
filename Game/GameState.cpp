#include "GameState.h"

GameState::GameState() {
	states = {
	PlayState::Home,
	PlayState::Targetting,
	PlayState::Shoot,
	PlayState::Quit,
	};

	currentState = states[0];
};

GameState::~GameState() {};

void GameState::nextState() {
	currentState = states[(currentState + 1) % states.size()];
}

void GameState::setState(PlayState& newState) {
	//Before changing state 

	currentState = newState;
	// after changing statae

}
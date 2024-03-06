#include "EngineStateMachine.h"

void GameState::nextState() {
	currentState = states[(currentState + 1) % states.size()];
}

void GameState::setState(EngineState& newState) {
	//Before changing state 

	currentState = newState;
	// after changing statae

}

GameState::GameState() {
	states = {
	EngineState::Message,
	EngineState::NewGameObject,
	EngineState::Render
	};

	currentState = states[0];
};

GameState::~GameState() {};


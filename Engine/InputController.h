#pragma once
#include "Utile.h"
#include <map>

using namespace std;

class InputManager {
private:
	~InputManager();
	
	map<string, bool> m_input;

public:
	InputManager();
	void keyList();
	map<string, bool> getKeyDown();
};
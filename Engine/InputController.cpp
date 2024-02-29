#include "InputController.h"

InputManager::InputManager()
{
	m_input["papagnanEscape"] = false;
}

void InputManager::keyList()
{
	(GetAsyncKeyState(VK_ESCAPE) & 0x01) ? m_input["papagnanEscape"] = true : m_input["papagnanEscape"] = false;
}

map<string, bool> InputManager::getKeyDown()
{
	return m_input;
}


InputManager::~InputManager()
{
}


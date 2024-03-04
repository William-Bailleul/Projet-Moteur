#include "InputController.h"

InputManager::InputManager()
{
	m_input["Escape"] = false;
}

void InputManager::keyList()
{
	(GetAsyncKeyState(VK_ESCAPE) & 0x01) ? m_input["Escape"] = true : m_input["Escape"] = false;
}

map<string, bool> InputManager::getKeyDown()
{
	return m_input;
}


InputManager::~InputManager()
{
}


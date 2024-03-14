#include "InputController.h"

InputManager::InputManager()
{
    m_input["Escape"] = 0;
    m_input["Z"] = 0;
    m_input["Q"] = 0;
    m_input["S"] = 0;
    m_input["D"] = 0;
    m_input["Shift"] = 0;
    m_input["Space"] = 0;
    m_input["ARROWRIGHT"] = 0;
    m_input["ARROWUP"] = 0;
    m_input["ARROWDOWN"] = 0;
    m_input["ARROWLEFT"] = 0;

}

InputManager::~InputManager() {

}

void InputManager::setKeyState(const char& key, const string& index) {
    if (GetAsyncKeyState(key) & 0x8000) {
        switch (m_input[index]) {
        case 0: // down
            m_input[index] = 1;
            break;
        case 1: // hold
            m_input[index] = 2;
            break;
        default:
            m_input[index] = 2;
            break;
        }
    }
    else if (m_input[index] != 0 && m_input[index] != 3) { // up
        m_input[index] = 3;
    }
    else {
        m_input[index] = 0;
    }
}

void InputManager::keyList() {
    setKeyState(VK_ESCAPE, escape);
    setKeyState('Z', accelerate);
    setKeyState('S', backwards);
    setKeyState('Q', yawLeft);
    setKeyState('D', yawRight);
    setKeyState(VK_LEFT, rollLeft);
    setKeyState(VK_RIGHT, rollRight);
    setKeyState(VK_SPACE, shoot);
    setKeyState(VK_SHIFT, boost);
    setKeyState(VK_UP, pitchDown);
    setKeyState(VK_DOWN, pitchUp);
}

bool InputManager::getKeyUp(const string& key) {
    auto iterator = m_input.find(key);
    int value = iterator->second;

    return (value == KEY_UP) ? true : false;
}

bool InputManager::getKeyDown(const string& key){
    auto iterator = m_input.find(key);
    int value = iterator->second;

    return (value == KEY_DOWN) ? true : false;
}

bool InputManager::getKey(const string& key) {
    auto iterator = m_input.find(key);
    int value = iterator->second;

    return (value == KEY_DOWN || value == KEY_HOLD) ? true : false;
}
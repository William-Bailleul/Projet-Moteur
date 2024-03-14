#include "InputController.h"

InputManager::InputManager()
{
    m_input["Escape"] = 0;
    m_input["Z"] = 0;
    m_input["Q"] = 0;
    m_input["S"] = 0;
    m_input["D"] = 0;
    m_input["A"] = 0;
    m_input["E"] = 0;
    m_input["LeftClick"] = 0;
    m_input["RightClick"] = 0;
    m_input["Space"] = 0;
    m_input["BACKARROW"] = 0;

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
    setKeyState('Z', pitchDown);
    setKeyState('Q', yawLeft);
    setKeyState('S', pitchUp);
    setKeyState('D', yawRight);
    setKeyState('A', rollLeft);
    setKeyState('E', rollRight);
    setKeyState(VK_LBUTTON, shoot);
    setKeyState(VK_RBUTTON, boost);
    setKeyState(VK_SPACE, accelerate);
    setKeyState(VK_DOWN, backwards);
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
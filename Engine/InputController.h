#pragma once

#include "Utile.h"
#include "defineKey.h"
#include <map>

using namespace std;

class InputManager {
public:
    InputManager();
    ~InputManager();

    void setKeyState(const char& key, const string& index);
    int getKeyState(const string& c);
    void keyList();

private:

    map<string, int> m_input;

};
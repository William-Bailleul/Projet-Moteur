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
    void keyList();

    bool getKey(const string& key);
    bool getKeyUp(const string& key);
    bool getKeyDown(const string& key);


private:

    map<string, int> m_input;

};
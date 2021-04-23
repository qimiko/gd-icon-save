#pragma once
#ifndef _MANAGERS_GAMEMANAGER_HPP
#define _MANAGERS_GAMEMANAGER_HPP

#include <cocos2d.h>

#include "gmanager.hpp"

class GameManager : public GManager {
public:
    static GameManager* sharedState();

    void toggleGameVariable(const char* variableName);
    void setGameVariable(const char* variableName, bool);
    bool getGameVariable(const char* variableName);

    void setIntGameVariable(const char* keyName, int);
    int getIntGameVariable(const char* keyName);

};

#endif

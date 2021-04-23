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

    inline int getPlayerBall() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1B8);
    }
    void setPlayerBall(int);

    inline int getPlayerBird() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1C4);
    }
    void setPlayerBird(int);

    inline int getPlayerColor() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1F4);
    }
    void setPlayerColor(int);

    inline int getPlayerColor2() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x200);
    }
    void setPlayerColor2(int);

    inline int getPlayerDeathEffect() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x218);
    }
    void setPlayerDeathEffect(int);

    inline int getPlayerFrame() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1A0);
    }
    void setPlayerFrame(int); // it took me _this_ long to realize this meant cube

    inline int getPlayerShip() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1AC);
    }
    void setPlayerShip(int);

    inline int getPlayerDart() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1D0);
    }
    void setPlayerDart(int);

    inline int getPlayerRobot() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1DC);
    }
    void setPlayerRobot(int);

    inline int getPlayerSpider() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x1E8);
    }
    void setPlayerSpider(int);

    inline int getPlayerStreak() const {
        return *reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(this) + 0x20C);
    }
    void setPlayerStreak(int);

    inline IconType getPlayerIconType() const {
        return *reinterpret_cast<IconType*>(reinterpret_cast<uintptr_t>(this) + 0x230);
    }
    inline void setPlayerIconType(IconType n_type) {
        auto icontype_ptr = reinterpret_cast<IconType*>(reinterpret_cast<uintptr_t>(this) + 0x230);
        *icontype_ptr = n_type;
    };

    inline bool getPlayerGlow() const
    {
        return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x22C);
    }
    inline void setPlayerGlow(bool n_glow) {
        auto glow_ptr = reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x22C);
        *glow_ptr = n_glow;
    };
};

#endif

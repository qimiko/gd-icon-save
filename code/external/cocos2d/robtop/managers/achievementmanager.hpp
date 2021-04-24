#pragma once
#ifndef _MANAGERS_ACHIEVEMENTMANAGER_HPP
#define _MANAGERS_ACHIEVEMENTMANAGER_HPP

#include <cocos2d.h>
#include <robtop/enums/unlocktype.hpp>

class AchievementManager : public cocos2d::CCNode {
public:
    static AchievementManager* sharedState();
    const char* achievementForUnlock(int, UnlockType);
    cocos2d::CCDictionary* getAchievementsWithID(const char*);
};

#endif

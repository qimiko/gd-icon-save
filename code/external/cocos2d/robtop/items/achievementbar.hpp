#pragma once
#ifndef _ITEMS_ACHIEVEMENTBAR_HPP
#define _ITEMS_ACHIEVEMENTBAR_HPP

#include <cocos2d.h>

class AchievementBar : public cocos2d::CCNode {
public:
    static AchievementBar* create(const char* title, const char* desc, const char* icon, bool isQuest);
    void show();
};

#endif

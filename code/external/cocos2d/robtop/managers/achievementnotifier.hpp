#pragma once
#ifndef _MANAGERS_ACHIEVEMENTNOTIFIER_HPP
#define _MANAGERS_ACHIEVEMENTNOTIFIER_HPP

#include <cocos2d.h>
#include <robtop/items/achievementbar.hpp>

class AchievementNotifier : public cocos2d::CCNode {
protected:
    cocos2d::CCScene* m_pCurrentScene;
    cocos2d::CCArray* m_pQueue;
    AchievementBar* m_pCurrentAchievement;
public:
    static AchievementNotifier* sharedState();
    void notifyAchievement(const char* title, const char* description,
        const char* icon, bool isQuest);
    void showNextAchievement();
};

#endif

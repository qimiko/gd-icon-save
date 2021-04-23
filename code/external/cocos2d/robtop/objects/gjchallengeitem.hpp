#pragma once
#ifndef _OBJECTS_GJCHALLENGEITEM_HPP
#define _OBJECTS_GJCHALLENGEITEM_HPP

#include <cocos2d.h>

class GJChallengeItem : public cocos2d::CCObject {
public:
    static GJChallengeItem* createWithCoder(DS_Dictionary*);
};

#endif
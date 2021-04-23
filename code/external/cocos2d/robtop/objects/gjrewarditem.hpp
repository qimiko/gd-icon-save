#pragma once
#ifndef _OBJECTS_GJREWARDITEM_HPP
#define _OBJECTS_GJREWARDITEM_HPP

#include <cocos2d.h>

class GJRewardItem : public cocos2d::CCObject {
public:
    static GJRewardItem* createWithCoder(DS_Dictionary*);
};

#endif
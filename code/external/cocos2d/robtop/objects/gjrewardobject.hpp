#pragma once
#ifndef _OBJECTS_GJREWARDOBJECT_HPP
#define _OBJECTS_GJREWARDOBJECT_HPP

#include <cocos2d.h>

class GJRewardObject : public cocos2d::CCObject {
public:
    static GJRewardObject* createWithCoder(DS_Dictionary*);
};

#endif
#pragma once
#ifndef _OBJECTS_GJGAMELEVEL_HPP
#define _OBJECTS_GJGAMELEVEL_HPP

#include <cocos2d.h>

class GJGameLevel : public cocos2d::CCNode {
public:
    static GJGameLevel* create();
    static GJGameLevel* createWithCoder(DS_Dictionary *);
};

#endif

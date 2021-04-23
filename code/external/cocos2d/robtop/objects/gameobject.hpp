#pragma once
#ifndef _OBJECTS_GAMEOBJECT_HPP
#define _OBJECTS_GAMEOBJECT_HPP

#include <cocos2d.h>

#include <robtop/sprites/ccspriteplus.hpp>

class GameObject : public CCSpritePlus {
public:
    static GameObject* createWithFrame(const char*);
    static GameObject* createWithKey(int);
};

#endif

#pragma once
#ifndef _SPRITES_GJITEMICON_HPP
#define _SPRITES_GJITEMICON_HPP

#include <cocos2d.h>

class GJItemIcon : public cocos2d::CCSprite {
public:
    static GJItemIcon* createBrowserItem(UnlockType, int);
};

#endif
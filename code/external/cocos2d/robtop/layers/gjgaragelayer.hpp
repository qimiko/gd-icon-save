#pragma once
#ifndef _LAYERS_GJGARAGELAYER_HPP
#define _LAYERS_GJGARAGELAYER_HPP

#include <cocos2d.h>

class GJGarageLayer : public cocos2d::CCLayer {
public:
    void updatePlayerSelect(cocos2d::CCNode* pushedBtn);
    void updateColorSelect(cocos2d::CCNode* pushedBtn, bool);
    void updatePlayerColors();
};

#endif
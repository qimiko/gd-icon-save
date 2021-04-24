#pragma once
#ifndef _LAYERS_SCROLLINGLAYER_HPP
#define _LAYERS_SCROLLINGLAYER_HPP

#include <cocos2d.h>

class ScrollingLayer : public cocos2d::CCLayerColor {
		static ScrollingLayer *create(cocos2d::CCSize, cocos2d::CCPoint, float);
};

#endif
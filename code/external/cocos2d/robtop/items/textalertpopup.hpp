#pragma once
#ifndef _ITEMS_TEXTALERTPOPUP_HPP
#define _ITEMS_TEXTALERTPOPUP_HPP

#include <cocos2d.h>

class TextAlertPopup : public cocos2d::CCNode {
public:
    static TextAlertPopup* create(std::string text, float duration, float width);
};

#endif
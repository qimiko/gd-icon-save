#pragma once
#ifndef _LAYERS_FLALERTLAYER_HPP
#define _LAYERS_FLALERTLAYER_HPP

#include <cocos2d.h>

#include <robtop/protocols/flalertlayerprotocol.hpp>

class FLAlertLayer : public cocos2d::CCLayerColor {
public:
    static FLAlertLayer* create(FLAlertLayerProtocol*, const char* title,
        std::string text, const char* leftBtn,
        const char* rightBtn);
    static FLAlertLayer* create(FLAlertLayerProtocol*, const char*,
        std::string text, const char*, const char*,
        float width);
    static FLAlertLayer*
    create(FLAlertLayerProtocol*, const char*, std::string text, const char*,
        const char*, float, bool isScrolling,
        float height); // scrolling dialog is created under assumption that
        // height >= 300

    virtual void show();
};

#endif

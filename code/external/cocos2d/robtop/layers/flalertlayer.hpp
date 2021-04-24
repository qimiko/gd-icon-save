#pragma once
#ifndef _LAYERS_FLALERTLAYER_HPP
#define _LAYERS_FLALERTLAYER_HPP

#include <cocos2d.h>

#include "scrollinglayer.hpp"

#include <robtop/protocols/flalertlayerprotocol.hpp>
#include <robtop/sprites/buttonsprite.hpp>

class FLAlertLayer : public cocos2d::CCLayerColor {
protected:
    // special thanks to shira :gron:
    cocos2d::CCMenu* btnMenu_;
    int controllersConnected_;
    FLAlertLayerProtocol* PParent_;
    cocos2d::CCScene* targetScene_;
    bool reverseKeyBack_ : 4;
    cocos2d::CCLayer* internalLayer_;
    int ZValue_;
    bool showInstant_ : 4;
    ButtonSprite* btn1_;
    ButtonSprite* btn2_;
    ScrollingLayer* scrollLayer_;
    int scrollTracker_;
    bool containsActions_;
    bool noBtnAction_;

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

    void registerWithTouchDispatcher();
};

#endif

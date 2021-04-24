#pragma once
#ifndef ICON_CLASSES_ICONKITWIDGET_HPP
#define ICON_CLASSES_ICONKITWIDGET_HPP

#include <cocos2dcpp.h>

#include <utility>
#include <vector>

#include "gamemanager_ext.hpp"
#include "iconkitobject.hpp"

namespace IconKit {
class IconKitWidget : public cocos2d::CCNode {
    CC_SYNTHESIZE_RETAIN(IconKitObject*, _kit_object, KitObject);
    CC_SYNTHESIZE_RETAIN(GJGarageLayer*, _garage_layer, GarageLayer);

    static IconKitWidget* create(IconKitObject* kit_obj)
    {
        IconKitWidget* pRet = new IconKitWidget();
        if (pRet && pRet->init(kit_obj)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

    virtual bool init(IconKitObject*);

    void onDeleteKit(cocos2d::CCObject*);
    void onUseKit(cocos2d::CCObject*);
};
}
#endif
#pragma once
#ifndef ICON_CLASSES_ICONKITDIALOG_HPP
#define ICON_CLASSES_ICONKITDIALOG_HPP

#include <cocos2dcpp.h>

#include <utility>
#include <vector>

#include "gamemanager_ext.hpp"
#include "iconkitobject.hpp"
#include "iconkitwidget.hpp"

namespace IconKit {
class IconKitDialog : public FLAlertLayer {
    CC_SYNTHESIZE_RETAIN(GJGarageLayer*, _garage_layer, GarageLayer);

    CREATE_FUNC(IconKitDialog);

    virtual bool init();

    void onClose(cocos2d::CCObject*) {
        this->setKeyboardEnabled(false);
        this->removeFromParentAndCleanup(true);
    };

    virtual void keyBackClicked() { this->onClose(nullptr); }
};
}
#endif
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
    CC_SYNTHESIZE(uint32_t, _list_count, ListCount);

    CREATE_FUNC(IconKitDialog);

    virtual bool init();

    void onClose(cocos2d::CCObject*)
    {
        this->setKeyboardEnabled(false);
        this->removeFromParentAndCleanup(true);
    };

    virtual void keyBackClicked() { this->onClose(nullptr); }

    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
    {
        // the layer is buggy if you try to scroll without there being enough to scroll
        if (this->scrollLayer_ != nullptr && this->scrollTracker_ == -1 && this->_list_count >= 3) {
            if (this->scrollLayer_->ccTouchBegan(pTouch, pEvent)) {
                this->scrollTracker_ = pTouch->getID();
            }
        }

        return true;
    };

    virtual void ccTouchCancelled(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
    {
        if (this->scrollTracker_ == pTouch->getID()) {
            this->scrollLayer_->ccTouchCancelled(pTouch, pEvent);
        }
    };

    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
    {
        if (this->scrollTracker_ == pTouch->getID()) {
            this->scrollLayer_->ccTouchEnded(pTouch, pEvent);
            this->scrollTracker_ = -1;
        }
    };

    virtual void ccTouchMoved(cocos2d::CCTouch* pTouch, cocos2d::CCEvent* pEvent)
    {
        if (this->scrollTracker_ == pTouch->getID()) {
            this->scrollLayer_->ccTouchMoved(pTouch, pEvent);
        }
    };
};
}
#endif
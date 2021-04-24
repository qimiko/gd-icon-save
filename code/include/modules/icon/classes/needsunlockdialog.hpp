#pragma once
#ifndef ICON_CLASSES_NEEDUNLOCKDIALOG_HPP
#define ICON_CLASSES_NEEDUNLOCKDIALOG_HPP

#include <cocos2dcpp.h>

#include <utility>
#include <vector>

#include "gamemanager_ext.hpp"
#include "iconkitobject.hpp"
#include "iconkitwidget.hpp"

namespace IconKit {
class NeedUnlockDialog : public FLAlertLayer {
protected:
    std::vector<std::pair<uint32_t, UnlockType>> _unlock_requirements;

public:
    static NeedUnlockDialog* create(std::vector<std::pair<uint32_t, UnlockType>> unlockRequirements)
    {
        NeedUnlockDialog* pRet = new NeedUnlockDialog();
        if (pRet && pRet->init(unlockRequirements)) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }

    bool init(std::vector<std::pair<uint32_t, UnlockType>> unlockRequirements);

    void onClose(cocos2d::CCObject*)
    {
        this->setKeyboardEnabled(false);
        this->removeFromParentAndCleanup(true);
    };

    virtual void keyBackClicked() { this->onClose(nullptr); }
};
}
#endif
#include "modules/icon/classes/needsunlockdialog.hpp"

using namespace IconKit;

bool NeedUnlockDialog::init(std::vector<std::pair<uint32_t, UnlockType>> unlockRequirements)
{
    if (this->initWithColor({ 0x00, 0x00, 0x00, 0x3B })) {
        auto ccd = cocos2d::CCDirector::sharedDirector();
        auto win_size = ccd->getWinSize();

        this->registerWithTouchDispatcher();

        auto td = ccd->getTouchDispatcher();
        td->incrementForcePrio(2);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        this->_unlock_requirements = unlockRequirements;

        this->internalLayer_ = cocos2d::CCLayer::create();
        this->addChild(this->internalLayer_);

        auto background = cocos2d::extension::CCScale9Sprite::create("square01_001.png", { 0.0f, 0.0f, 94.0f, 94.0f });
        background->setContentSize(cocos2d::CCSize(350.0f, 250.0f));
        background->setPosition(win_size.width / 2, win_size.height / 2);
        this->internalLayer_->addChild(background);

        auto layer_label = cocos2d::CCLabelBMFont::create("Required Unlocks For Set", "goldFont.fnt");
        this->internalLayer_->addChild(layer_label);
        layer_label->setPosition(win_size.width / 2, (win_size.height / 2) + 95.0f);
        layer_label->setScale(0.8f);

        constexpr auto initial_displacement = -115.0f;

        // actual layer stuff here
        auto gm = GameManager::sharedState();

        auto icon_count = 1u;
        auto pos_x_tracker = (win_size.width / 2) + initial_displacement;
        auto pos_y_tracker = (win_size.height / 2) + 55.0f;

        for (const auto& icon : unlockRequirements) {
            auto item_icon = GJItemIcon::createBrowserItem(icon.second, icon.first);
            this->internalLayer_->addChild(item_icon);

            item_icon->setPosition(cocos2d::CCPoint(pos_x_tracker, pos_y_tracker));

            pos_x_tracker += 75.0f;
            if (icon_count % 4 == 0) {
                pos_x_tracker = (win_size.width / 2) + initial_displacement;
                pos_y_tracker += -45.0f;
            }

            icon_count++;
        }

        // close btn
        auto close_btn_menu = cocos2d::CCMenu::create();
        this->internalLayer_->addChild(close_btn_menu);

        auto close_btn_sprite = ButtonSprite::create("OK");

        auto close_btn = CCMenuItemSpriteExtra::create(
            close_btn_sprite,
            nullptr,
            this,
            static_cast<cocos2d::SEL_MenuHandler>(&NeedUnlockDialog::onClose));

        close_btn_menu->addChild(close_btn);
        close_btn->setPosition(0.0f, -90.0f);

        return true;
    }
    return false;
}
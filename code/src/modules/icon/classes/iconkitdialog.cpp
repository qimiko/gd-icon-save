#include "modules/icon/classes/iconkitdialog.hpp"

using namespace IconKit;

bool IconKitDialog::init()
{
    if (this->initWithColor({ 0x00, 0x00, 0x00, 0x3B })) {
        auto ccd = cocos2d::CCDirector::sharedDirector();
        auto win_size = ccd->getWinSize();

        this->registerWithTouchDispatcher();

        auto td = ccd->getTouchDispatcher();
        td->incrementForcePrio(2);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        this->internalLayer_ = cocos2d::CCLayer::create();
        this->addChild(this->internalLayer_);

        auto background = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
        background->setContentSize(cocos2d::CCSize(420.0f, 280.0f));
        background->setPosition(win_size.width / 2, win_size.height / 2);
        this->internalLayer_->addChild(background);

        auto layer_label = cocos2d::CCLabelBMFont::create("Saved Icons", "bigFont.fnt");
        this->internalLayer_->addChild(layer_label);
        layer_label->setPosition(win_size.width / 2, (win_size.height / 2) + 120.0f);
        layer_label->setScale(0.8f);

        // actual layer stuff here
        auto gm = GameManager::sharedState();
        auto ext_obj = dynamic_cast<GameManager_ext*>(gm->getUserObject());
        if (ext_obj != nullptr) {
            auto stored_kits = ext_obj->getStoredKits();
            for (uint32_t i = 0; i < stored_kits->count(); ++i) {
                auto widget = IconKitWidget::create(dynamic_cast<IconKitObject*>(stored_kits->objectAtIndex(i)));
                this->internalLayer_->addChild(widget);
								// anchor point seems to be off, don't know why though
                widget->setPosition(win_size.width / 2, (win_size.height / 2) + (i * -92.0f) + 40.0f);
            }
        }

        // close btn
        auto close_btn_menu = cocos2d::CCMenu::create();
        this->internalLayer_->addChild(close_btn_menu);

        auto close_btn_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");

        auto close_btn = CCMenuItemSpriteExtra::create(
            close_btn_sprite,
            nullptr,
            this,
            static_cast<cocos2d::SEL_MenuHandler>(&IconKitDialog::onClose));

        close_btn_menu->addChild(close_btn);
        close_btn->setPosition(-210.0f, 130.0f);

        return true;
    }
    return false;
}
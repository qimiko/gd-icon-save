#include "modules/icon/classes/iconkitdialog.hpp"

using namespace IconKit;

bool IconKitDialog::init(GJGarageLayer* garage)
{
    if (this->initWithColor({ 0x00, 0x00, 0x00, 0x3B })) {
        auto ccd = cocos2d::CCDirector::sharedDirector();
        auto win_size = ccd->getWinSize();

        this->registerWithTouchDispatcher();

        auto td = ccd->getTouchDispatcher();
        td->incrementForcePrio(2);

        this->setKeypadEnabled(true);
        this->setTouchEnabled(true);

        this->setGarageLayer(garage);

        this->internalLayer_ = cocos2d::CCLayer::create();
        this->addChild(this->internalLayer_);

        auto background = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", { 0.0f, 0.0f, 80.0f, 80.0f });
        background->setContentSize(cocos2d::CCSize(420.0f, 280.0f));
        background->setPosition(win_size.width / 2, win_size.height / 2);
        this->internalLayer_->addChild(background);

        auto layer_label = cocos2d::CCLabelBMFont::create("Saved Icons", "bigFont.fnt");
        this->internalLayer_->addChild(layer_label);
        layer_label->setPosition(win_size.width / 2, (win_size.height / 2) + 115.0f);
        layer_label->setScale(0.8f);

        // actual layer stuff here
        auto gm = GameManager::sharedState();
        auto ext_obj = dynamic_cast<GameManager_ext*>(gm->getUserObject());
        if (ext_obj != nullptr) {
            auto stored_kits = ext_obj->getStoredKits();
            this->setListCount(stored_kits->count());

            if (this->_list_count != 0) {
                constexpr auto distance_between_frames = 92.0f;

                auto scrolling_layer = ScrollingLayer::create(
                    cocos2d::CCSize(415.0f, 226.0f),
                    cocos2d::CCPoint(win_size.width / 2, (win_size.height / 2) - 20.0f),
                    distance_between_frames * this->getListCount() - 200.0f);

                this->internalLayer_->addChild(scrolling_layer);
                this->scrollLayer_ = scrolling_layer;

                auto scrolling_scale_parent = *reinterpret_cast<cocos2d::CCNode**>(reinterpret_cast<uintptr_t>(scrolling_layer) + 0x1CC);
                scrolling_scale_parent = this->internalLayer_;

                auto scrolling_internal_layer = *reinterpret_cast<cocos2d::CCLayer**>(reinterpret_cast<uintptr_t>(scrolling_layer) + 0x1C8);

                for (uint32_t i = 0; i < this->getListCount(); ++i) {
                    auto widget = IconKitWidget::create(dynamic_cast<IconKitObject*>(stored_kits->objectAtIndex(i)));
                    scrolling_internal_layer->addChild(widget);

                    if (this->_garage_layer != nullptr) {
                        widget->setGarageLayer(this->_garage_layer);
                    }
                    // anchor point seems to be off, don't know why though
                    widget->setPosition(win_size.width / 2, (win_size.height / 2) + (i * -distance_between_frames) + 40.0f);
                }
            } else {
                auto none_saved_label = cocos2d::CCLabelBMFont::create("No icons saved :(", "goldFont.fnt");
                this->internalLayer_->addChild(none_saved_label);

                none_saved_label->setPosition(win_size.width / 2, win_size.height / 2);
            }
        }
        this->scrollTracker_ = -1;

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
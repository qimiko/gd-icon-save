#include "modules/default.hpp"

namespace {

class SupportLayerBtnHelper : public cocos2d::CCNode {
public:
    void onLicense(cocos2d::CCObject* target)
    {
        auto license_dialog = FLAlertLayer::create(nullptr, "Legal",
            R"###(<cy>Cappuccino License</c>
Copyright (c) 2021 AndreNIH

This work is licensed under the terms of the MIT license.
For a copy, see <https://opensource.org/licenses/MIT>.

<cy>cocos2d-x License (v2.2)</c>
Copyright (c) 2010-2011 - cocos2d-x community
(see each file to see the different copyright owners)

This work is licensed under the terms of the MIT license.
For a copy, see <https://opensource.org/licenses/MIT>.

<cy>Geometry Dash</c>
Copyright (c) 2013-2021 RobtopGames

This modified application is provided under the assumption and restriction that the user owns a license to the original product.)###",
            "OK", nullptr, 400.0f, true, 300.0f);
        license_dialog->show();
    }
};

void (*SupportLayer_customSetup_O)(SupportLayer*);
void SupportLayer_customSetup_H(SupportLayer* self)
{
    SupportLayer_customSetup_O(self);

    auto internal_layer = get_from_offset<cocos2d::CCLayer*>(self, 0x1B4);

    auto director = cocos2d::CCDirector::sharedDirector();

    auto legal_menu = cocos2d::CCMenu::create();
    internal_layer->addChild(legal_menu);

    auto legal_sprite = ButtonSprite::create(
        "Legal", 220, 0, 0.4f, false, "bigFont.fnt", "GJ_button_05.png", 25.0f);

    auto legal_button = CCMenuItemSpriteExtra::create(
        legal_sprite, nullptr, self,
        static_cast<cocos2d::SEL_MenuHandler>(&SupportLayerBtnHelper::onLicense));

    legal_menu->addChild(legal_button);

    auto legal_button_position = cocos2d::CCPoint(60.0f, -90.0f);
    legal_button->setPosition(legal_button_position);

    return;
}

bool (*MoreOptionsLayer_init_O)(MoreOptionsLayer*);
bool MoreOptionsLayer_init_H(MoreOptionsLayer* self)
{
    auto return_val = MoreOptionsLayer_init_O(self);
    auto page_count = ptr_to_offset<int>(self, 0x1DC);

    auto next_page_objects = self->objectsForPage(*page_count);

    auto version_string = cocos2d::CCString::createWithFormat(
        "GD Mod u%i.%i.%i-%s\n(%s)\nCompiled: %s",
        CMakeConfiguration::VER_MAJOR, CMakeConfiguration::VER_MINOR,
        CMakeConfiguration::VER_PATCH, CMakeConfiguration::HASH,
        CMakeConfiguration::COMMIT_SUBJECT, CMakeConfiguration::COMPILE_TIME);

    auto label = cocos2d::CCLabelBMFont::create(version_string->getCString(),
        "chatFont.fnt");
    self->addChild(label);

    label->setAlignment(cocos2d::CCTextAlignment::kCCTextAlignmentLeft);
    label->setScale(0.5f);

    auto director = cocos2d::CCDirector::sharedDirector();
    auto window_size = director->getWinSize();
    auto label_position = cocos2d::CCPoint(window_size.width / 2,
        (director->getScreenBottom()) + 50.0f);

    self->convertToNodeSpace(label_position);

    label->setPosition(label_position);

    label->setVisible(false);
    next_page_objects->addObject(label);

    return return_val;
}
} // namespace

namespace Default {
void Module::on_initialize()
{
    HookHandler::get_handler()
        .add_hook(get_sym_addr("_ZN12SupportLayer11customSetupEv"), SupportLayer_customSetup_H, &SupportLayer_customSetup_O)
        .add_hook<10>(get_sym_addr("_ZN16MoreOptionsLayer4initEv"), MoreOptionsLayer_init_H, &MoreOptionsLayer_init_O);
}
} // namespace Default

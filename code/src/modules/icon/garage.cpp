#include "modules/icon/garage.hpp"

namespace {
using namespace IconKit;

class GJGarageLayer_ext : public GJGarageLayer {
public:
    void onSaveIcons(cocos2d::CCObject* target)
    {
        auto dialog = IconKitDialog::create(this);

        dialog->show();
    }
};

bool (*GJGarageLayer_init_O)(GJGarageLayer* self);
bool GJGarageLayer_init_H(GJGarageLayer* self)
{
    if (GJGarageLayer_init_O(self)) {
        auto open_iconkits_sprite = cocos2d::CCSprite::createWithSpriteFrameName("gj_folderBtn_001.png");
        auto open_iconkits_btn = CCMenuItemSpriteExtra::create(
            open_iconkits_sprite,
            nullptr,
            self,
            static_cast<cocos2d::SEL_MenuHandler>(&GJGarageLayer_ext::onSaveIcons));

        auto open_iconkits_menu = cocos2d::CCMenu::create();
        open_iconkits_menu->addChild(open_iconkits_btn);
        self->addChild(open_iconkits_menu);

        auto ccd = cocos2d::CCDirector::sharedDirector();

        open_iconkits_menu->setPosition(ccd->getScreenLeft() + 30.0f, ccd->getScreenBottom() + 100.0f);

        return true;
    }

    return false;
}
}

namespace IconKit::Garage {
void Module::on_initialize()
{
    HookHandler::get_handler()
        .add_hook(get_sym_addr("_ZN13GJGarageLayer4initEv"), GJGarageLayer_init_H, &GJGarageLayer_init_O);
}
}
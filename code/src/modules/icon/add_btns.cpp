#include "modules/icon/add_btns.hpp"

namespace {
using namespace IconKit;

class ProfilePage_ext : public ProfilePage {
public:
    void onSaveIcons(cocos2d::CCObject* target)
    {
        auto score = get_from_offset<GJUserScore*>(this, 0x1E8);

        auto icon = new IconKitObject();
        icon->setCubeID(score->getPlayerCube());
        icon->setShipID(score->getPlayerShip());
        icon->setBallID(score->getPlayerBall());
        icon->setUfoID(score->getPlayerUfo());
        icon->setWaveID(score->getPlayerWave());
        icon->setRobotID(score->getPlayerRobot());
        icon->setSpiderID(score->getPlayerSpider());
        icon->setStreakID(score->getPlayerStreak());
        icon->setDeathID(score->getPlayerExplosion());
        icon->setPlayerFrame(score->getIconType());
        icon->setHasGlow(score->getGlowEnabled());
        icon->setColor1(score->getPlayerColor1());
        icon->setColor2(score->getPlayerColor2());

        auto gm = GameManager::sharedState();
        auto ext_obj = dynamic_cast<GameManager_ext*>(gm->getUserObject());
        if (ext_obj != nullptr) {
            ext_obj->getStoredKits()->addObject(icon);

            auto popup = TextAlertPopup::create("Icons saved", 0.5f, 0.6f);
            this->addChild(popup, 100);
        }
    }
};

void (*ProfilePage_loadPageFromUserInfo_O)(ProfilePage*, GJUserScore*);
void ProfilePage_loadPageFromUserInfo_H(ProfilePage* self, GJUserScore* user)
{
    ProfilePage_loadPageFromUserInfo_O(self, user);

    auto download_icon_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
    auto save_icon_btn = CCMenuItemSpriteExtra::create(
        download_icon_sprite,
        nullptr,
        self,
        static_cast<cocos2d::SEL_MenuHandler>(&ProfilePage_ext::onSaveIcons));

    auto save_btn_menu = cocos2d::CCMenu::create();
    save_btn_menu->addChild(save_icon_btn);

    auto internal_layer = reinterpret_cast<cocos2d::CCLayer*>(self->getChildren()->objectAtIndex(0));
    internal_layer->addChild(save_btn_menu, 48);

    save_icon_btn->setPosition(-194.0f, 41.0f);
}

class GJGarageLayer_ext : public GJGarageLayer {
public:
    void onSaveIcons(cocos2d::CCObject* target)
    {
        // this will likely involve some level of reverse gamemanager
        auto gm = GameManager::sharedState();

        auto icon = new IconKitObject();
        icon->setCubeID(gm->getPlayerFrame());
        icon->setShipID(gm->getPlayerShip());
        icon->setBallID(gm->getPlayerBall());
        icon->setUfoID(gm->getPlayerBird());
        icon->setWaveID(gm->getPlayerDart());
        icon->setRobotID(gm->getPlayerRobot());
        icon->setSpiderID(gm->getPlayerSpider());
        icon->setStreakID(gm->getPlayerStreak());
        icon->setDeathID(gm->getPlayerDeathEffect());
        icon->setPlayerFrame(gm->getPlayerIconType());
        icon->setHasGlow(gm->getPlayerGlow());
        icon->setColor1(gm->getPlayerColor());
        icon->setColor2(gm->getPlayerColor2());

        auto ext_obj = dynamic_cast<GameManager_ext*>(gm->getUserObject());
        if (ext_obj != nullptr) {
            ext_obj->getStoredKits()->addObject(icon);

            auto popup = TextAlertPopup::create("Icons saved", 0.5f, 0.6f);
            this->addChild(popup, 100);
        }
    }
};

bool (*GJGarageLayer_init_O)(GJGarageLayer* self);
bool GJGarageLayer_init_H(GJGarageLayer* self)
{
    if (GJGarageLayer_init_O(self)) {
        auto download_icon_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadBtn_001.png");
        auto save_icon_btn = CCMenuItemSpriteExtra::create(
            download_icon_sprite,
            nullptr,
            self,
            static_cast<cocos2d::SEL_MenuHandler>(&GJGarageLayer_ext::onSaveIcons));

        auto save_btn_menu = cocos2d::CCMenu::create();
        save_btn_menu->addChild(save_icon_btn);
        self->addChild(save_btn_menu);

        auto ccd = cocos2d::CCDirector::sharedDirector();

        save_btn_menu->setPosition(ccd->getScreenLeft() + 70.0f, ccd->getScreenTop() - 23.0f);

        return true;
    }

    return false;
}

}

namespace IconKit::Btns {
void Module::on_initialize()
{
    HookHandler::get_handler()
        .add_hook(get_sym_addr("_ZN11ProfilePage20loadPageFromUserInfoEP11GJUserScore"), ProfilePage_loadPageFromUserInfo_H, &ProfilePage_loadPageFromUserInfo_O)
        .add_hook(get_sym_addr("_ZN13GJGarageLayer4initEv"), GJGarageLayer_init_H, &GJGarageLayer_init_O);
}
}
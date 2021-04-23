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

				auto gm = GameManager::sharedState();
				auto ext_obj = dynamic_cast<GameManager_ext *>(gm->getUserObject());
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

    auto download_icon_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_downloadsIcon_001.png");
    auto download_btn_sprite = ButtonSprite::create(download_icon_sprite);

    auto save_icon_btn = CCMenuItemSpriteExtra::create(
        download_btn_sprite,
        nullptr,
        self,
        static_cast<cocos2d::SEL_MenuHandler>(&ProfilePage_ext::onSaveIcons));

    auto save_btn_menu = cocos2d::CCMenu::create();
    save_btn_menu->addChild(save_icon_btn);

    auto internal_layer = reinterpret_cast<cocos2d::CCLayer*>(self->getChildren()->objectAtIndex(0));
    internal_layer->addChild(save_btn_menu, 48);

    save_icon_btn->setPosition(-194.0f, 43.0f);
}

}

namespace IconKit::Btns {
void Module::on_initialize()
{
    HookHandler::get_handler()
        .add_hook(get_sym_addr("_ZN11ProfilePage20loadPageFromUserInfoEP11GJUserScore"), ProfilePage_loadPageFromUserInfo_H, &ProfilePage_loadPageFromUserInfo_O);
}
}
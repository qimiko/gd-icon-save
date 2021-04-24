#include "modules/icon/classes/iconkitwidget.hpp"

using namespace IconKit;

void IconKitWidget::onDeleteKit(cocos2d::CCObject* target)
{
    auto gm = GameManager::sharedState();
    auto ext_obj = dynamic_cast<GameManager_ext*>(gm->getUserObject());
    if (ext_obj != nullptr) {
        ext_obj->getStoredKits()->removeObject(this->getKitObject());
    }

    this->removeFromParentAndCleanup(true);
}

void IconKitWidget::onUseKit(cocos2d::CCObject* target)
{
    auto gm = GameManager::sharedState();

    auto icon = this->getKitObject();

    gm->setPlayerFrame(icon->getCubeID());
    gm->setPlayerShip(icon->getShipID());
    gm->setPlayerBall(icon->getBallID());
    gm->setPlayerBird(icon->getUfoID());
    gm->setPlayerDart(icon->getWaveID());
    gm->setPlayerRobot(icon->getRobotID());
    gm->setPlayerSpider(icon->getSpiderID());
    gm->setPlayerStreak(icon->getStreakID());
    gm->setPlayerDeathEffect(icon->getDeathID());
    gm->setPlayerIconType(icon->getPlayerFrame());
    gm->setPlayerGlow(icon->getHasGlow());
    gm->setPlayerColor(icon->getColor1());
    gm->setPlayerColor2(icon->getColor2());

    if (this->getGarageLayer() != nullptr) {
        // update simpleplayer there :)
    }

    auto ccd = cocos2d::CCDirector::sharedDirector();
    auto win_size = ccd->getWinSize();
    auto center_point = cocos2d::CCPoint(win_size.width / 2, win_size.height / 2);
    this->convertToNodeSpace(center_point);

    auto popup = TextAlertPopup::create("Icons loaded", 0.5f, 0.6f);
    this->addChild(popup, 100);
    popup->setPosition(center_point);
}

bool IconKitWidget::init(IconKitObject* kit_obj)
{
    this->setKitObject(kit_obj);

    auto widget_bg = cocos2d::extension::CCScale9Sprite::create("GJ_square01.png", cocos2d::CCRect(0.0f, 0.0f, 80.0f, 80.0f));
    this->addChild(widget_bg);

    widget_bg->setContentSize(cocos2d::CCSize(400.0f, 90.0f));

    std::vector<std::pair<uint32_t, IconType>> icons {
        { kit_obj->getCubeID(), IconType::Cube },
        { kit_obj->getShipID(), IconType::Ship },
        { kit_obj->getBallID(), IconType::Ball },
        { kit_obj->getUfoID(), IconType::Ufo },
        { kit_obj->getWaveID(), IconType::Wave },
        { kit_obj->getRobotID(), IconType::Robot },
        { kit_obj->getSpiderID(), IconType::Spider }
    };

    auto gm = GameManager::sharedState();

    auto player_color1 = gm->colorForIdx(kit_obj->getColor1());
    auto player_color2 = gm->colorForIdx(kit_obj->getColor2());

    auto current_icon_position = -170.0f;
    auto position_addition = 47.0f;

    for (const auto& icon : icons) {
        auto player_frame = SimplePlayer::create(1);
        player_frame->updatePlayerFrame(icon.first, icon.second);
        player_frame->setColor(player_color1);
        player_frame->setSecondColor(player_color2);

        if (kit_obj->getHasGlow()) {
            player_frame->setPlayerGlow(true);
            player_frame->updateColors();
        }

        this->addChild(player_frame);

        player_frame->setPositionX(current_icon_position);
        player_frame->setPositionY(0.0f);
        current_icon_position += position_addition;
    }

    auto kit_actions_menu = cocos2d::CCMenu::create();
    this->addChild(kit_actions_menu);

    auto delete_kit_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
    auto delete_kit_btn = CCMenuItemSpriteExtra::create(
        delete_kit_sprite,
        nullptr,
        this,
        static_cast<cocos2d::SEL_MenuHandler>(&IconKitWidget::onDeleteKit));

    auto use_kit_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_selectSongBtn_001.png");
    auto use_kit_btn = CCMenuItemSpriteExtra::create(
        use_kit_sprite,
        nullptr,
        this,
        static_cast<cocos2d::SEL_MenuHandler>(&IconKitWidget::onUseKit));

    kit_actions_menu->addChild(delete_kit_btn);
    kit_actions_menu->addChild(use_kit_btn);

    kit_actions_menu->setPosition(170.0f, 0.0f);
    delete_kit_btn->setPositionY(20.0f);
    use_kit_btn->setPositionY(-20.0f);

    return true;
}
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

std::vector<std::pair<uint32_t, UnlockType>> IconKitWidget::getRequiredUnlocks()
{
    auto gm = GameManager::sharedState();
    auto icon = this->getKitObject();

    std::vector<std::pair<uint32_t, UnlockType>> locked_icons;

    std::vector<std::tuple<uint32_t, IconType, UnlockType>> icons {
        std::make_tuple(icon->getCubeID(), IconType::Cube, UnlockType::Icon),
        std::make_tuple(icon->getShipID(), IconType::Ship, UnlockType::Ship),
        std::make_tuple(icon->getBallID(), IconType::Ball, UnlockType::Ball),
        std::make_tuple(icon->getUfoID(), IconType::Ufo, UnlockType::Ufo),
        std::make_tuple(icon->getWaveID(), IconType::Wave, UnlockType::Wave),
        std::make_tuple(icon->getRobotID(), IconType::Robot, UnlockType::Robot),
        std::make_tuple(icon->getSpiderID(), IconType::Spider, UnlockType::Spider),
        std::make_tuple(icon->getDeathID(), IconType::DeathEffect, UnlockType::Death),
        std::make_tuple(icon->getStreakID(), IconType::Special, UnlockType::Streak),
    };

    for (const auto& icon : icons) {
        if (!gm->isIconUnlocked(std::get<0>(icon), std::get<1>(icon))) {
            locked_icons.push_back({ std::get<0>(icon), std::get<2>(icon) });
        }
    }

    if (!gm->isColorUnlocked(icon->getColor1(), false)) {
        locked_icons.push_back({ icon->getColor1(), UnlockType::Color });
    }

    if (!gm->isColorUnlocked(icon->getColor2(), true)) {
        locked_icons.push_back({ icon->getColor2(), UnlockType::Color2 });
    }

    if (icon->getHasGlow() && !gm->isIconUnlocked(2, IconType::Special)) {
        locked_icons.push_back({ 2, UnlockType::Streak });
    }

    return locked_icons;
}

void IconKitWidget::onUseKit(cocos2d::CCObject* target)
{
    if (auto req_unlocks = this->getRequiredUnlocks(); req_unlocks.size() > 0) {
        NeedUnlockDialog::create(req_unlocks)->show();
        return;
    }

    auto gm = GameManager::sharedState();
    auto icon = this->getKitObject();

    gm->setPlayerFrame(icon->getCubeID());
    gm->setPlayerShip(icon->getShipID());
    gm->setPlayerBall(icon->getBallID());
    gm->setPlayerBird(icon->getUfoID());
    gm->setPlayerDart(icon->getWaveID());
    gm->setPlayerRobot(icon->getRobotID());
    gm->setPlayerSpider(icon->getSpiderID());
    gm->setPlayerStreak(std::max(icon->getStreakID(), 1u));
    gm->setPlayerDeathEffect(icon->getDeathID());
    gm->setPlayerIconType(icon->getPlayerFrame());
    gm->setPlayerGlow(icon->getHasGlow());
    gm->setPlayerColor(icon->getColor1());
    gm->setPlayerColor2(icon->getColor2());

    auto ccd = cocos2d::CCDirector::sharedDirector();
    auto win_size = ccd->getWinSize();
    auto center_point = cocos2d::CCPoint(win_size.width / 2, win_size.height / 2);
    this->convertToNodeSpace(center_point);

    if (this->_garage_layer != nullptr) {
        auto garage_preview = *reinterpret_cast<SimplePlayer**>(reinterpret_cast<uintptr_t>(this->_garage_layer) + 0x134);

        auto id = 1u;
        switch (icon->getPlayerFrame()) {
        case IconType::Cube:
            id = icon->getCubeID();
            break;
        case IconType::Ship:
            id = icon->getShipID();
            break;
        case IconType::Ball:
            id = icon->getBallID();
            break;
        case IconType::Ufo:
            id = icon->getUfoID();
            break;
        case IconType::Wave:
            id = icon->getWaveID();
            break;
        case IconType::Robot:
            id = icon->getRobotID();
            break;
        case IconType::Spider:
            id = icon->getSpiderID();
            break;
        default:
            break;
        }

        garage_preview->updatePlayerFrame(id, icon->getPlayerFrame());
        this->_garage_layer->updatePlayerColors();
    }

    // the scrollinglayer we use takes charge over literally every other thing in the game besides yet another alert
    auto popup = FLAlertLayer::create(nullptr, "Icons loaded", "Custom icon kit has been loaded to your user.", "OK", nullptr);
    popup->show();
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
    if (auto req_unlocks = this->getRequiredUnlocks(); req_unlocks.size() > 0) {
        use_kit_sprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_reportBtn_001.png");
        use_kit_sprite->setScale(0.8f);
    }

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
#pragma once
#ifndef ICON_CLASSES_ICONKITOBJECT_HPP
#define ICON_CLASSES_ICONKITOBJECT_HPP

#include <cocos2dcpp.h>

namespace IconKit {
class IconKitObject : public cocos2d::CCObject {
    CC_SYNTHESIZE(uint32_t, _cube_id, CubeID);
    CC_SYNTHESIZE(uint32_t, _ship_id, ShipID);
    CC_SYNTHESIZE(uint32_t, _ball_id, BallID);
    CC_SYNTHESIZE(uint32_t, _ufo_id, UfoID);
    CC_SYNTHESIZE(uint32_t, _wave_id, WaveID);
    CC_SYNTHESIZE(uint32_t, _robot_id, RobotID);
    CC_SYNTHESIZE(uint32_t, _spider_id, SpiderID);
    CC_SYNTHESIZE(uint32_t, _streak_id, StreakID);
    CC_SYNTHESIZE(uint32_t, _death_id, DeathID);
    CC_SYNTHESIZE(IconType, _player_frame, PlayerFrame);

    CC_SYNTHESIZE(uint32_t, _col_1, Color1);
    CC_SYNTHESIZE(uint32_t, _col_2, Color2);

    CC_SYNTHESIZE(bool, _has_glow, HasGlow);

public:
    virtual bool canEncode() { return true; }

    void load_from_dictionary(DS_Dictionary* dict)
    {
        this->_cube_id = dict->getIntegerForKey("k1");
        this->_ship_id = dict->getIntegerForKey("k2");
        this->_ball_id = dict->getIntegerForKey("k3");
        this->_ufo_id = dict->getIntegerForKey("k4");
        this->_wave_id = dict->getIntegerForKey("k5");
        this->_robot_id = dict->getIntegerForKey("k6");
        this->_spider_id = dict->getIntegerForKey("k7");
        this->_streak_id = dict->getIntegerForKey("k8");
        this->_death_id = dict->getIntegerForKey("k9");
        this->_player_frame = static_cast<IconType>(dict->getIntegerForKey("k10"));
        this->_has_glow = dict->getBoolForKey("k11");
        this->_col_1 = dict->getIntegerForKey("k12");
        this->_col_2 = dict->getIntegerForKey("k13");
    }

    virtual void encodeWithCoder(DS_Dictionary* dict)
    {
        dict->setIntegerForKey("kCEK", 53);

        dict->setIntegerForKey("k1", this->_cube_id);
        dict->setIntegerForKey("k2", this->_ship_id);
        dict->setIntegerForKey("k3", this->_ball_id);
        dict->setIntegerForKey("k4", this->_ufo_id);
        dict->setIntegerForKey("k5", this->_wave_id);
        dict->setIntegerForKey("k6", this->_robot_id);
        dict->setIntegerForKey("k7", this->_spider_id);
        dict->setIntegerForKey("k8", this->_streak_id);
        dict->setIntegerForKey("k9", this->_death_id);
        dict->setIntegerForKey("k10", static_cast<int>(this->_player_frame));

        dict->setBoolForKey("k11", this->_has_glow);
        dict->setIntegerForKey("k12", this->_col_1);
        dict->setIntegerForKey("k13", this->_col_2);
    }

    static IconKitObject* createWithCoder(DS_Dictionary* dict) {
			auto obj = new IconKitObject();
			obj->load_from_dictionary(dict);
			return obj;
		}
};
}

#endif
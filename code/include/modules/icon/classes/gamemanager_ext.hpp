#pragma once
#ifndef ICON_CLASSES_GAMEMANAGER_EXT_HPP
#define ICON_CLASSES_GAMEMANAGER_EXT_HPP

#include <cocos2dcpp.h>

namespace IconKit {
class GameManager_ext : public cocos2d::CCObject {
	CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, stored_kits, StoredKits);
};
}

#endif
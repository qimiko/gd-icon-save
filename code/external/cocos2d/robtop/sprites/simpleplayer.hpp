#pragma once
#ifndef _SPRITES_SIMPLEPLAYER_HPP
#define _SPRITES_SIMPLEPLAYER_HPP

#include <cocos2d.h>

class SimplePlayer : public cocos2d::CCSprite {
public:
	static SimplePlayer* create(int frameID);
	void updatePlayerFrame(int, IconType);
	void updateColors();

	virtual void setColor(cocos2d::ccColor3B const&);
	void setSecondColor(cocos2d::ccColor3B const&);

	inline bool getPlayerGlow() const
	{
			return *reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x204);
	}
	inline void setPlayerGlow(bool n_glow)
	{
			auto glow_ptr = reinterpret_cast<bool*>(reinterpret_cast<uintptr_t>(this) + 0x204);
			*glow_ptr = n_glow;
	};
};

#endif
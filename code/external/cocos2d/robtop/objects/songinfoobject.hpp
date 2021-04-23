#pragma once
#ifndef _OBJECTS_SONGINFOOBJECT_HPP
#define _OBJECTS_SONGINFOOBJECT_HPP

#include <cocos2d.h>

class SongInfoObject : public cocos2d::CCNode {
public:
    static SongInfoObject* createWithCoder(DS_Dictionary*);
};

#endif
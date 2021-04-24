#pragma once
#ifndef _OBJECTS_OBJECTDECODER_HPP
#define _OBJECTS_OBJECTDECODER_HPP

#include <cocos2d.h>

class ObjectDecoder : public cocos2d::CCNode {
public:
    static ObjectDecoder* sharedDecoder();
    virtual cocos2d::CCObject* getDecodedObject(int, DS_Dictionary*);
};

#endif
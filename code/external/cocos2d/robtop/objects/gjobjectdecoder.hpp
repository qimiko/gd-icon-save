#pragma once
#ifndef _OBJECTS_GJOBJECTDECODER_HPP
#define _OBJECTS_GJOBJECTDECODER_HPP

#include <cocos2d.h>

class GJObjectDecoder : public ObjectDecoder {
public:
    virtual cocos2d::CCObject* getDecodedObject(int, DS_Dictionary*);
};

#endif
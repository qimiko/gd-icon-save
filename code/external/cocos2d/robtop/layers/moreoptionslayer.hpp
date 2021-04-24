#pragma once
#ifndef _LAYERS_MOREOPTIONSLAYER_HPP
#define _LAYERS_MOREOPTIONSLAYER_HPP

#include "flalertlayer.hpp"
#include <cocos2d.h>

#include <robtop/protocols/googleplaydelegate.hpp>
#include <robtop/protocols/textinputdelegate.hpp>

class MoreOptionsLayer : public FLAlertLayer, public TextInputDelegate, public GooglePlayDelegate {
public:
    cocos2d::CCArray* objectsForPage(int page);
};

#endif
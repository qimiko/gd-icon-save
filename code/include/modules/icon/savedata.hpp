#pragma once
#ifndef MODULES_ICON_SAVEDATA_HPP
#define MODULES_ICON_SAVEDATA_HPP

#include <cocos2dcpp.h>

#include "./classes/gamemanager_ext.hpp"
#include "./classes/iconkitobject.hpp"

#include "base/hook_handler.hpp"
#include "base/module.hpp"

namespace IconKit::SaveData {
class Module : public Base::Module {
protected:
    void on_initialize();
};
}

#endif

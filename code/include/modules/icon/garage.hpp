#pragma once
#ifndef MODULES_ICON_GARAGE_HPP
#define MODULES_ICON_GARAGE_HPP

#include <cocos2dcpp.h>

#include "./classes/gamemanager_ext.hpp"
#include "./classes/iconkitobject.hpp"
#include "./classes/iconkitwidget.hpp"
#include "./classes/iconkitdialog.hpp"

#include "base/hook_handler.hpp"
#include "base/module.hpp"

namespace IconKit::Garage {
class Module : public Base::Module {
protected:
    void on_initialize();
};
}

#endif

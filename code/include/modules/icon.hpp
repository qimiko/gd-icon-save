#pragma once
#ifndef MODULES_ICON_HPP
#define MODULES_ICON_HPP

#include "base/module.hpp"
#include "./icon/savedata.hpp"

namespace IconKit {
class Module : public Base::Module {
protected:
    void on_initialize();
};
}

#endif
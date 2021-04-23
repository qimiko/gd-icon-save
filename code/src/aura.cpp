#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <cocos2dcpp.h>

#include <vector>

#include "base/hook_handler.hpp"
#include "modules/modules.hpp"

__attribute__((constructor)) void aqua()
{
    setup_handle();

    std::vector<Base::Module*> modules {
        new Default::Module(), new IconKit::Module()
    };

    for (const auto& module : modules) {
        module->initialize();
    }

    HookHandler::get_handler().install_hooks();
}
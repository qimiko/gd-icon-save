#include "modules/icon.hpp"

namespace IconKit {
void Module::on_initialize()
{
    IconKit::SaveData::Module().initialize();
    IconKit::Btns::Module().initialize();

    return;
}
}
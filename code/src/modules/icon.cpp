#include "modules/icon.hpp"

namespace IconKit {
void Module::on_initialize()
{
    (new IconKit::SaveData::Module())->initialize();

    return;
}
}
#include "modules/icon/savedata.hpp"

namespace {

using namespace IconKit;

void (*GameManager_dataLoaded_O)(GameManager* self, DS_Dictionary* dict);
void GameManager_dataLoaded_H(GameManager* self, DS_Dictionary* dict)
{
    GameManager_dataLoaded_O(self, dict);

    auto ext_data = new GameManager_ext();
    self->setUserObject(ext_data);

    ext_data->setStoredKits(dict->getArrayForKey("EXT_iconKit", false));
}

void (*GameManager_encodeDataTo_O)(GameManager* self, DS_Dictionary* dict);
void GameManager_encodeDataTo_H(GameManager* self, DS_Dictionary* dict)
{
    GameManager_encodeDataTo_O(self, dict);

    auto ext_data = dynamic_cast<GameManager_ext*>(self->getUserObject());
    if (ext_data != nullptr) {
        dict->setArrayForKey("EXT_iconKit", ext_data->getStoredKits());
    }
}

cocos2d::CCObject* (*GJObjectDecoder_getDecodedObject_O)(GJObjectDecoder*, int, DS_Dictionary*);
cocos2d::CCObject* GJObjectDecoder_getDecodedObject_H(GJObjectDecoder* self, int type, DS_Dictionary* dict)
{
    // note, hooking virtuals has the stupidest trampoline back
    // since this function is relatively simple idc about remaking it
    // but obviously this shouldn't be a thing i have to do
    switch (type) {
    case 4:
        return GJGameLevel::createWithCoder(dict);
    // case 5 seems be a removed class or something, no clue honestly
    case 6:
        return SongInfoObject::createWithCoder(dict);
    case 7:
        return GJChallengeItem::createWithCoder(dict);
    case 8:
        return GJRewardItem::createWithCoder(dict);
    case 9:
        return GJRewardObject::createWithCoder(dict);
    case 53:
        return IconKitObject::createWithCoder(dict);
    default:
        cocos2d::CCLog("Unimp Obj Decoder: %i", type);
        return nullptr;
    }
}
}

namespace IconKit::SaveData {
void Module::on_initialize()
{
    HookHandler::get_handler()
        .add_hook(get_sym_addr("_ZN11GameManager10dataLoadedEP13DS_Dictionary"), GameManager_dataLoaded_H, &GameManager_dataLoaded_O)
        .add_hook(get_sym_addr("_ZN11GameManager12encodeDataToEP13DS_Dictionary"), GameManager_encodeDataTo_H, &GameManager_encodeDataTo_O)
        .add_hook(get_sym_addr("_ZN15GJObjectDecoder16getDecodedObjectEiP13DS_Dictionary"), GJObjectDecoder_getDecodedObject_H, &GJObjectDecoder_getDecodedObject_O);
}
}
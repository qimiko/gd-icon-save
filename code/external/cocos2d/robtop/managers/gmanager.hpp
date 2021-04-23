#pragma once
#ifndef _MANAGERS_GMANAGER_HPP
#define _MANAGERS_GMANAGER_HPP

#include <cocos2d.h>

class GManager : public cocos2d::CCNode {
    protected:
        std::string m_sFileName;
        bool m_bSetup;
        bool m_bSaved;

    public:
        void save();
        virtual void setup();
        virtual void encodeDataTo(DS_Dictionary* data);
        virtual void dataLoaded(DS_Dictionary* data);
        virtual void firstLoad();
};

#endif

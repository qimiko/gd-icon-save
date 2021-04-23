#pragma once
#ifndef _PROTOCOLS_GOOGLEPLAYDELEGATE_HPP
#define _PROTOCOLS_GOOGLEPLAYDELEGATE_HPP

class GooglePlayDelegate {
public:
    virtual void googlePlaySignedIn() = 0;
};

#endif
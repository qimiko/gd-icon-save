#pragma once
#ifndef _PROTOCOLS_TEXTINPUTDELEGATE_HPP
#define _PROTOCOLS_TEXTINPUTDELEGATE_HPP

class TextInputDelegate {
public:
    virtual bool textChanged(CCTextInputNode*) = 0;
    virtual bool textInputClosed(CCTextInputNode*) = 0;
    virtual bool textInputOpened(CCTextInputNode*) = 0;
    virtual bool textInputShouldOffset(CCTextInputNode*) = 0;
    virtual bool textInputReturn(CCTextInputNode*) = 0;
    virtual bool allowTextInput(CCTextInputNode*) { return 1; };
};

#endif
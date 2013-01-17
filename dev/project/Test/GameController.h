#pragma once
#include <cocos2d.h>
using namespace cocos2d;

class GameController: public CCLayer
{
private:
    CCPoint m_tBeginPos;
protected:
public:
    GameController();
    ~GameController();

    void         showMainMenu();
    void         testCallback(CCObject* sender);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
};
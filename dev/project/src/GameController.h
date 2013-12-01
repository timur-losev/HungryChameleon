#pragma once

class GameController: public CCLayer
{
private:
    CCPoint m_tBeginPos;
protected:
public:
    GameController();
    ~GameController();

    virtual bool            init();
    virtual void            start();

    virtual void            ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void            ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
};
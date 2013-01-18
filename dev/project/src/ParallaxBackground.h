#pragma once

class ParallaxBackground : public CCLayer
{
private:
protected:
public:
    ParallaxBackground();
    ~ParallaxBackground();

    bool                        init();
    static ParallaxBackground*  create();

    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
};
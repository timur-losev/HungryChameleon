#pragma once

class ParallaxBackground : public CCLayer
{
public:
    typedef std::function<void (CCTouch* touch)> OnTouchEventSignature_t;
private:
    OnTouchEventSignature_t m_TouchesEndedCallback;
    OnTouchEventSignature_t m_TouchesMovedCallback;
    OnTouchEventSignature_t m_TouchesBeganCallback;
protected:
public:
    ParallaxBackground();
    ~ParallaxBackground();

    bool                        init();
    static ParallaxBackground*  create();

    void Scroll(CCTouch*);

    void RegisterTouchBeganCallback(const OnTouchEventSignature_t& callback);
    void RegisterTouchEndCallback(const OnTouchEventSignature_t& callback);
    void RegisterTouchMovedCallback(const OnTouchEventSignature_t& callback);

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};
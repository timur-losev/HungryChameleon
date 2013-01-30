#pragma once

class ParallaxBackground : public CCLayer
{
private:
	std::function<void (CCTouch* touch)> m_TouchesEndedCallback;
	std::function<void (CCTouch* touch)> m_TouchesMovedCallback;
protected:
public:
    ParallaxBackground();
    ~ParallaxBackground();

    bool                        init();
    static ParallaxBackground*  create();

	void Scroll(CCTouch*);

	void RegisterTouchBeganCallback(std::function<void (CCTouch* touch)> callback) { m_TouchesEndedCallback = callback; }
	void RegisterTouchMovedCallback(std::function<void (CCTouch* touch)> callback) { m_TouchesMovedCallback = callback; }

    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
};
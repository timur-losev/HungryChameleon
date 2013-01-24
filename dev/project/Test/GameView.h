#pragma once
#include <cocos2d.h>
#include "GameScene.h"

using namespace cocos2d;

class GameView: public CCLayer
{
private:
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

	std::function<void (CCTouch* touch)> m_TouchesBeginCallback;
	CCTouch m_PrevTouch;
protected:
public:
    GameView();
    ~GameView();

	void RegisterTouchCallback(std::function<void (CCTouch* touch)> callback) { m_TouchesBeginCallback = callback; };
};


#include "GameView.h"
#include "VisibleRect.h"

GameView::GameView()
{
	CCSprite* sprite = CCSprite::create("data/background.png");
	sprite->retain();
	sprite->setPosition( ccp( VisibleRect::center().x, VisibleRect::center().y) );

	addChild(sprite);

    setTouchEnabled(true);
}

GameView::~GameView()
{
}

void GameView::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

	if (!m_TouchesBeginCallback._Empty())
	{
		m_TouchesBeginCallback(touch);
	}
}
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
	if (it != pTouches->end())
	{
		CCTouch* touch = (CCTouch*)(*it);
		m_PrevTouch.setTouchInfo(touch->getID(), touch->getLocationInView().x, touch->getLocationInView().y);
	}
}

void GameView::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	if (it != pTouches->end())
	{
		if (m_TouchesMovedCallback)
		{
			m_TouchesMovedCallback((CCTouch*)(*it));
		}
	}
}

void GameView::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

	m_PrevTouch.setTouchInfo(m_PrevTouch.getID(), m_PrevTouch.getLocationInView().x, m_PrevTouch.getLocationInView().y);
	m_PrevTouch.setTouchInfo(touch->getID(), touch->getLocationInView().x, touch->getLocationInView().y);

	if (m_TouchesBeginCallback)
	{
		m_TouchesBeginCallback(&m_PrevTouch);
	}
}
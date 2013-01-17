#include "GameView.h"
#include "VisibleRect.h"

GameView::GameView()
{
	CCSprite* sprite = CCSprite::create("data/background.png");
	sprite->setPosition( ccp( VisibleRect::center().x, VisibleRect::center().y) );

	addChild(sprite);

    setTouchEnabled(true);
}

GameView::~GameView()
{
}


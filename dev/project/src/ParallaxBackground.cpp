#include "pch.h"
#include "ParallaxBackground.h"
#include "VisibleRect.h"

ParallaxBackground::ParallaxBackground()
{

}

ParallaxBackground::~ParallaxBackground()
{

}

bool ParallaxBackground::init()
{
    if (CCLayer::init())
    {
        setTouchEnabled(true);

        CCSprite* pBackground = CCSprite::create();
        pBackground->initWithFile("main_bg.png");
        pBackground->setPosition(VisibleRect::center());

        CCSprite* pMiddleground = CCSprite::create();
        pMiddleground->initWithFile("main_mg.png");
        pMiddleground->setPosition(VisibleRect::center());

        CCSprite* pForegraund = CCSprite::create();
        pForegraund->initWithFile("main_fg.png");
        pForegraund->setPosition(VisibleRect::center());

        CCParallaxNode* voidNode = CCParallaxNode::create();
        voidNode->addChild(pBackground, -1, ccp(0.1f, 0.1f), VisibleRect::center());
        voidNode->addChild(pMiddleground, 1, ccp(1.2f, 1.2f), VisibleRect::center());
        voidNode->addChild(pForegraund, 2, ccp(2.0f, 2.f), VisibleRect::center());

        addChild(voidNode, 0, 0);

        return true;
    }

    return false;
}

ParallaxBackground* ParallaxBackground::create()
{
    ParallaxBackground *pRet = new ParallaxBackground();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void ParallaxBackground::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();
    CCPoint diff = touch->getDelta();

    CCNode* node = getChildByTag(0);
    CCPoint currentPos = node->getPosition();
    node->setPosition( currentPos.x + diff.x, currentPos.y );
}
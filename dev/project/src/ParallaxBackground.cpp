#include "Precompiled.h"
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
        pBackground->initWithFile("Background/-1.png");
        pBackground->setPosition(VisibleRect::center());

        CCSprite* pMiddleground = CCSprite::create();
        pMiddleground->initWithFile("Background/1.png");
        pMiddleground->setPosition(VisibleRect::center());

        CCSprite* pForegraund = CCSprite::create();
        pForegraund->initWithFile("Background/2.png");
        pForegraund->setPosition(VisibleRect::center());

        CCSprite* pStatic = CCSprite::create();
        pStatic->initWithFile("Background/3.png");
        pStatic->setPosition(VisibleRect::center());

        CCParallaxNode* voidNode = CCParallaxNode::create();
        voidNode->addChild(pBackground, -1, ccp(-1.3f, 1.3f), VisibleRect::center());
        voidNode->addChild(pMiddleground, 1, ccp(-1.0f, 1.0f), VisibleRect::center());
        voidNode->addChild(pForegraund, 2, ccp(0.1f, 0.5f), VisibleRect::center());
        voidNode->addChild(pStatic, 3, ccp(0.0f, 0.0f), VisibleRect::center());


        addChild(voidNode, 0, 0);

        return true;
    }

    return false;
}

ParallaxBackground* ParallaxBackground::create()
{
    ParallaxBackground *pRet = new ParallaxBackground();
    if (pRet->init())
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

void ParallaxBackground::Scroll(CCTouch* touch)
{
    CCPoint diff = touch->getDelta();

    CCNode* node = getChildByTag(0);
    CCPoint currentPos = node->getPosition();
    float xpos = currentPos.x + diff.x;
    float ypos = currentPos.y/* + diff.y*/;

    ypos = std::max(ypos, -35.f);
    ypos = std::min(ypos, 35.f);

    xpos = std::max(xpos, -50.f);
    xpos = std::min(xpos, 50.f);

    node->setPosition(xpos , ypos );
}

void ParallaxBackground::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    if (it != pTouches->end())
    {
        CCTouch* touch = static_cast<CCTouch*>(*it);
    }
}

void ParallaxBackground::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCTouch *touch = (CCTouch*)pTouches->anyObject();

    if (touch)
    {
        if (m_TouchesMovedCallback)
        {
            m_TouchesMovedCallback(touch);
        }
    }
}

void ParallaxBackground::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = static_cast<CCTouch*>(*it);

    if (m_TouchesEndedCallback)
    {
        m_TouchesEndedCallback(touch);
    }
}

void ParallaxBackground::RegisterTouchBeganCallback( const OnTouchEventSignature_t& callback )
{
    m_TouchesEndedCallback = callback;
}

void ParallaxBackground::RegisterTouchMovedCallback( const OnTouchEventSignature_t& callback )
{
    m_TouchesMovedCallback = callback;
}

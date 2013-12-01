#include "Precompiled.h"

#include "GameController.h"
#include "GameDelegate.h"

static CCPoint s_tCurPos = CCPointZero;

GameController::GameController()
{
}

GameController::~GameController()
{

}

void GameController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation(); 
}

bool GameController::init()
{
    bool bRet = CCLayer::init();

    return bRet;
}

void GameController::start()
{
     setTouchEnabled(true);
     SharedGameDelegate::Instance().startGame();
}

void GameController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    /*CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    CCPoint touchLocation = touch->getLocation();    
    float nMoveY = touchLocation.y - m_tBeginPos.y;

    CCPoint curPos  = m_pItemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

    if (nextPos.y < 0.0f)
    {
        m_pItemMenu->setPosition(CCPointZero);
        return;
    }

    if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }

    m_pItemMenu->setPosition(nextPos);
    m_tBeginPos = touchLocation;
    s_tCurPos   = nextPos;*/
}
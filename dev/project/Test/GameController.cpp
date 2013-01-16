#include "GameController.h"
#include "GameScene.h"

static CCPoint s_tCurPos = CCPointZero;

GameController::GameController()
{

}

GameController::~GameController()
{

}

void GameController::showMainMenu()
{
    setTouchEnabled(true);

	GameScene* mmscene = new GameScene();
    mmscene->createInstance();
    mmscene->release(); //this scene has been added to CCDirector pool. So, do release here
}

void GameController::testCallback(CCObject* sender)
{
    int i = 0;
}

void GameController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);

    m_tBeginPos = touch->getLocation(); 
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
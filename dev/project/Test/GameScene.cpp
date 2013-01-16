#include "GameScene.h"
#include "GameView.h"

GameScene::GameScene()
{

}

GameScene::~GameScene()
{

}

void GameScene::onEnter()
{
    CCScene::onEnter();

}

void GameScene::createInstance()
{
    m_pGameView = new GameView();
    //m_pGameView->getStartButton()->setTarget(this, menu_selector(GameViewScene::startCallback));

    addChild(m_pGameView);
    m_pGameView->autorelease();
    
    CCDirector::sharedDirector()->replaceScene(this);
}
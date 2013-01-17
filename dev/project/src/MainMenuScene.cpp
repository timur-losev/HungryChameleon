#include "pch.h"
#include "MainMenuScene.h"
#include "MainMenuView.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

//------------------------------------------------------------------//
MainMenuScene::MainMenuScene(): m_pMainMenu(nullptr)
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onEnter()
{
    GameSceneBase::onEnter();

}

bool MainMenuScene::init(bool fromGame)
{
    if (GameSceneBase::init())
    {
        CCSprite* pBackground = CCSprite::create();
        pBackground->initWithFile("data/mmbg.png");
        pBackground->setPosition(VisibleRect::center());

        m_pMainMenu = new MainMenuView();
        m_pMainMenu->init(fromGame);

        if (fromGame)
        {
            m_pMainMenu->getStartButton()->setTarget(this, menu_selector(MainMenuScene::returnCallback));
        }
        else
        {
            m_pMainMenu->getStartButton()->setTarget(this, menu_selector(MainMenuScene::startCallback));
        }

        addChild(pBackground);
        addChild(m_pMainMenu);
        m_pMainMenu->release();

        return true;
    }

    return false;
}

void MainMenuScene::startCallback(CCObject * pSender)
{
    GameDelegate::sharedGameDelegate()->startGame();
}


void MainMenuScene::returnCallback( CCObject * pSender )
{
    GameDelegate::sharedGameDelegate()->returnToGame();
}

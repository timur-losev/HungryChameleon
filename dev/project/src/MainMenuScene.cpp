#include "Precompiled.h"
#include "MainMenuScene.h"
#include "MainMenuView.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

//------------------------------------------------------------------//
MainMenuScene::MainMenuScene()
	:GameSceneBase(ESMMainMenu),
	m_pMainMenu(nullptr)

{
}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onEnter()
{
    GameSceneBase::onEnter();
	init(false);
}

bool MainMenuScene::init(bool fromGame)
{
    if (GameSceneBase::init())
    {
        m_pMainMenu = new MainMenuView();
        m_pMainMenu->init(fromGame);

        if (fromGame)
        {
			m_pMainMenu->getStartButton()->addTouchEventListener(this, toucheventselector(MainMenuScene::startCallback));
        }
        else
        {
			m_pMainMenu->getStartButton()->addTouchEventListener(this, toucheventselector(MainMenuScene::startCallback));
        }

        addChild(m_pMainMenu);
        m_pMainMenu->release();

        return true;
    }

    return false;
}

void MainMenuScene::startCallback(CCObject * pSender, extension::TouchEventType)
{
	_AdvanceToScene(ESMAction);
}


void MainMenuScene::returnCallback(CCObject * pSender, extension::TouchEventType)
{
//	SharedGameDelegate::Instance().returnToGame();
}

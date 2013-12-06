#include "Precompiled.h"
#include "MainMenuScene.h"
#include "MainMenuView.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

//------------------------------------------------------------------//
MainMenuScene::MainMenuScene()
	:GameSceneBase(ESMMainMenu)
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

		//setTouchEnabled(true);

		extension::UILayer* ul = extension::UILayer::create();
		extension::GUIReader reader;

		ul->addWidget(reader.widgetFromJsonFile("MainMenu/MainMenu.ExportJson"));
		m_pStartButton = ul->getWidgetByName("btn_start");
		m_pStartButton->addTouchEventListener(this, toucheventselector(MainMenuScene::startCallback));
		addChild(ul);

        return true;
    }

    return false;
}

void MainMenuScene::startCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
		_AdvanceToScene(ESMAction);
}


void MainMenuScene::returnCallback(CCObject * pSender, extension::TouchEventType)
{
//	SharedGameDelegate::Instance().returnToGame();
}

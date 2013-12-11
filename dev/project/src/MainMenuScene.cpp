#include "Precompiled.h"
#include "MainMenuScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

#include "PopupOk.h"
#include "PopupController.h"

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

		ul->addWidget(reader.widgetFromJsonFile("MainMenu/Background.ExportJson"));
		ul->addWidget(reader.widgetFromJsonFile("MainMenu/MainMenu.ExportJson"));
		m_pStartButton = ul->getWidgetByName("btn_start");
		m_pStartButton->addTouchEventListener(this, toucheventselector(MainMenuScene::_startCallback));
		addChild(ul);

		m_pStartButton = ul->getWidgetByName("btn_options");
		m_pStartButton->addTouchEventListener(this, toucheventselector(MainMenuScene::_optionsCallback));


        return true;
    }

    return false;
}

void MainMenuScene::_startCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
		_advanceToScene(ESMAction);
}


void MainMenuScene::returnCallback(CCObject * pSender, extension::TouchEventType)
{
//	SharedGameDelegate::Instance().returnToGame();
}

void MainMenuScene::_onUpdate(float dt)
{

}

void MainMenuScene::_optionsCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		PopupOk* p = new PopupOk();
		p->init("Well, Hello There!");
		GameDelegate::getPopupController()->queuePopup(p);
	}
}
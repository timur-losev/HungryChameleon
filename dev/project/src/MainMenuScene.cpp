#include "Precompiled.h"
#include "MainMenuScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

#include "PopupOk.h"
#include "PopupController.h"
#include "PopupLanguage.h"

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
		extension::UILayer* ul = extension::UILayer::create();
		extension::GUIReader reader;

		ul->addWidget(reader.widgetFromJsonFile("MainMenu/Background.ExportJson"));
		ul->addWidget(reader.widgetFromJsonFile("MainMenu/MainMenu.ExportJson"));

		extension::UIWidget* button;

		button = ul->getWidgetByName("btn_start");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(MainMenuScene::_startCallback));
		}

		button = ul->getWidgetByName("btn_options");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(MainMenuScene::_optionsCallback));
		}

		button = ul->getWidgetByName("btn_shop");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(MainMenuScene::_shopCallback));
		}
		addChild(ul);

        return true;
    }

    return false;
}

void MainMenuScene::_startCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
		_advanceToScene(ESMStoryMap);
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
		PopupLanguage* p = new PopupLanguage();
		GameDelegate::getPopupController()->queuePopup(p);
	}
}

void MainMenuScene::_shopCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		PopupOk* p = new PopupOk("Well, Hello There!");
		GameDelegate::getPopupController()->queuePopup(p);
	}
}
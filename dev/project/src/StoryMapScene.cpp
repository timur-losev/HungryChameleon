#include "Precompiled.h"
#include "StoryMapScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

#include "PopupOk.h"
#include "PopupController.h"
#include "PopupLanguage.h"
#include "Player.h"
#include "EventController.h"

//------------------------------------------------------------------//
StoryMapScene::StoryMapScene()
	:GameSceneBase(ESMMainMenu)
{
}

StoryMapScene::~StoryMapScene()
{

}

bool StoryMapScene::init()
{
    if (GameSceneBase::init())
    {
		extension::UILayer* ul = extension::UILayer::create();
		extension::GUIReader reader;

		ul->addWidget(reader.widgetFromJsonFile("MainMenu/StoryMap.ExportJson"));
		ul->addWidget(reader.widgetFromJsonFile("MainMenu/TopBar.ExportJson"));

		extension::UIWidget* storyMap = ul->getWidgetByName("story_map");
		assert(storyMap);

		Player* player = SharedGameDelegate::Instance().getPlayer();

		extension::UIWidget* tokenPos = storyMap->getChildByName(player->getTokenMapPositionName().c_str());
		assert(tokenPos);
		extension::UIWidget* token = ul->getWidgetByName("chameleon");
		assert(token);
		token->removeFromParent();
		tokenPos->addChild(token);


		CCArray* children = storyMap->getChildren();
		CCObject* child;
		CCARRAY_FOREACH(children, child)
		{
			extension::UIButton* levelButton = dynamic_cast<extension::UIButton*>(child);
			if (levelButton)
			{
				levelButton->addTouchEventListener(this, toucheventselector(StoryMapScene::_startSceneCallback));
				
				const char* name = levelButton->getName();
				const CCString* status = player->getStoryProgress()->valueForKey(name);
				if (status && status->intValue())
				{
					
				}
				else
				{
					levelButton->setButtonDisabled();
					CCInteger* intStatus = CCInteger::create(0);
					player->getStoryProgress()->setObject(intStatus, name);
				}
			}
		}


		extension::UIWidget* button;
		button = ul->getWidgetByName("btn_start");

		button = ul->getWidgetByName("btn_score_0");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(StoryMapScene::_optionsCallback));
		}

		button = ul->getWidgetByName("btn_cash_0");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(StoryMapScene::_shopCallback));
		}
		addChild(ul);

        return true;
    }

    return false;
}

void StoryMapScene::_startSceneCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		extension::UIWidget* widget = static_cast<extension::UIWidget*>(pSender);
		SharedEventController::Instance().gameStartedWithLevel(widget->getName());
		m_advanceToScene(ESMAction);
	}
}

void StoryMapScene::_onUpdate(float dt)
{

}

void StoryMapScene::_optionsCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		//PopupLanguage* p = new PopupLanguage();
		//SharedGameDelegate::Instance().getPopupController()->queuePopup(p);
		m_advanceToScene(ESMLeaderboard);
	}
}

void StoryMapScene::_shopCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		//PopupOk* p = new PopupOk("Well, Hello There!");
		//SharedGameDelegate::Instance().getPopupController()->queuePopup(p);
		m_advanceToScene(ESMMainMenu);
	}
}
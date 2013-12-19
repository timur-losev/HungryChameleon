#include "Precompiled.h"
#include "LeaderboardScene.h"
#include "GameDelegate.h"
#include "OnlineController.h"

using namespace extension;

//------------------------------------------------------------------//
LeaderboardScene::LeaderboardScene()
	:GameSceneBase(ESMLeaderboard)
{
}

LeaderboardScene::~LeaderboardScene()
{

}

void LeaderboardScene::onEnter()
{
    GameSceneBase::onEnter();
	init(false);
}

bool LeaderboardScene::init(bool fromGame)
{
    if (GameSceneBase::init())
    {
		UILayer* ul = extension::UILayer::create();
		GUIReader reader;

		ul->addWidget(reader.widgetFromJsonFile("MainMenu/Background.ExportJson"));
		ul->addWidget(reader.widgetFromJsonFile("MainMenu/Leaderboard.ExportJson"));

		UIWidget* button;

		button = ul->getWidgetByName("close");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(LeaderboardScene::_startCallback));
		}


		button = ul->getWidgetByName("btn_score_0");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(LeaderboardScene::_optionsCallback));
		}
		button = ul->getWidgetByName("btn_cash_0");
		if (button)
		{
			button->addTouchEventListener(this, toucheventselector(LeaderboardScene::_shopCallback));
		}

		//UIWidget* base = ul->getWidgetByName("base");
		UIScrollView* base = static_cast<UIScrollView*>(ul->getWidgetByName("base"));
		UIWidget* entry = ul->getWidgetByName("entry");

		if (entry && base)
		{
#if 0
			LeaderboardEntries_t records;
			records.push_back(LeaderboardEntry("Andrey", 1350, 1));
			records.push_back(LeaderboardEntry("Victor", 1301, 2));
			records.push_back(LeaderboardEntry("Denis", 1210, 3));
			records.push_back(LeaderboardEntry("Коля", 1115, 4));
			records.push_back(LeaderboardEntry("Альберт", 1101, 5));
			records.push_back(LeaderboardEntry("윤", 903, 6));
			records.push_back(LeaderboardEntry("Gregoriy", 850, 7));
			records.push_back(LeaderboardEntry("Щірий Я", 700, 8));
			records.push_back(LeaderboardEntry("Піндосам НІ!", 695, 9));
			records.push_back(LeaderboardEntry("Фак ю", 200, 10));
			records.push_back(LeaderboardEntry("Ноу, Фак ю", 199, 11));
			_initWithRecords(base, entry, records);
#else
			_initWithRecords(base, entry, GameDelegate::getOnlineController()->getEntries());
#endif
		}

		addChild(ul);

        return true;
    }

    return false;
}

void LeaderboardScene::_startCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
		_advanceToScene(ESMStoryMap);
}


void LeaderboardScene::returnCallback(CCObject * pSender, extension::TouchEventType)
{
//	SharedGameDelegate::Instance().returnToGame();
}

void LeaderboardScene::_onUpdate(float dt)
{

}

void LeaderboardScene::_optionsCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		_advanceToScene(ESMMainMenu);
	}
}

void LeaderboardScene::_shopCallback(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		_advanceToScene(ESMLeaderboard);
	}
}

void LeaderboardScene::_initWithRecords(UIScrollView* base, UIWidget* entry, const LeaderboardEntries_t& records)
{
	base->removeAllChildrenAndCleanUp(true);
	float entryHeight = entry->getRect().size.height;
	float containerHeight = records.size() * entryHeight;
	base->setInnerContainerSize(ccp(base->getInnerContainerSize().width, containerHeight));

	// get top of the container and substract entry height as it's anchor is left bottom corner
	CCPoint position = ccp(0, containerHeight - entryHeight);
	for (int a = 0; a < records.size(); ++a)
	{
		const LeaderboardEntry& record = records[a];

		UIWidget* copy = entry->clone();
		UILabel* rank = static_cast<UILabel*>(copy->getChildByName("rank"));
		UILabel* name = static_cast<UILabel*>(copy->getChildByName("name"));
		UILabel* score = static_cast<UILabel*>(copy->getChildByName("score"));
		std::stringstream ss;
		ss << record.rank;
		rank->setText(ss.str().c_str());
		ss.str("");
		ss << record.score;
		score->setText(ss.str().c_str());
		name->setText(record.name.c_str());

		//copy->removeFromParent();
		base->/*getInnerContainer()->*/addChild(copy);
		copy->setPosition(position);
		copy->setVisible(true);
		position.y -= entryHeight;
	}
}

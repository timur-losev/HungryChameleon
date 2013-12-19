#include "Precompiled.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

#include "Cell.h"
#include "CellField.h"
#include "Player.h"
#include "EventController.h"
#include "PopupController.h"
#include "PopupLanguage.h"
#include "LevelSettingsController.h"

MainScene::MainScene()
	: GameSceneBase(ESMAction)
//	, m_CellField(nullptr)
{
}

MainScene::~MainScene()
{
}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Atlas/Atlas0.plist");

	extension::UILayer* w = extension::UILayer::create();
	extension::GUIReader r;

	const std::string& levelName = GameDelegate::getLevelSettingsController()->
		getSettingsForPoint(GameDelegate::getPlayer()->getTokenMapPositionName()).levelName;

	w->addWidget(r.widgetFromJsonFile(levelName.c_str()));
	w->addWidget(m_topBar = r.widgetFromJsonFile("MainMenu/TopBar.ExportJson"));
	w->addWidget(r.widgetFromJsonFile("MainMenu/MainScene.ExportJson"));
	addChild(w);

	_setScore(GameDelegate::getPlayer()->getHighScore());

	extension::UIWidget* button;

	button = w->getWidgetByName("btn_score_0");
	if (button)
	{
		button->addTouchEventListener(this, toucheventselector(MainScene::_onCheatFinishGame));
	}
	button = w->getWidgetByName("btn_cash_0");
	if (button)
	{
		button->addTouchEventListener(this, toucheventselector(MainScene::_onPauseButtonPressed));
	}

	extension::UIWidget* cellFieldContainer = w->getWidgetByName("720-16:9");
	if (cellFieldContainer)
	{
		CellField* cellField = new CellField();
		float width = cellFieldContainer->getSize().width / CellField::MatrixVisibleLineSize;
		float height = cellFieldContainer->getSize().height / CellField::MatrixVisibleLineSize;
		assert(cellField->init(width, height));
		addChild(cellField);
		cellField->setTouchEnabled(true);
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(cellField, 0, true);
		//cellField->setAnchorPoint(ccp(0, 0));
		cellField->setPosition(cellFieldContainer->getPosition());
		cellField->release();
	}

	return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();
}

void MainScene::onMainMenuTap( CCObject* )
{
	_advanceToScene(ESMMainMenu);
}

void MainScene::_onUpdate(float dt)
{
}

void MainScene::RemoveFlyingBubbles(CCNode* sender)
{

}

void MainScene::_setScore(int value)
{
	if (!m_topBar)
		return;

	extension::UILabel* textField = dynamic_cast<extension::UILabel*>(m_topBar->getChildByName("txt_score_0"));
	if (!textField)
		return;
	
	char buffer[10];
	sprintf(buffer, "%05d", value);
	textField->setText(buffer);
}

void MainScene::_setCash(int value)
{

}

void MainScene::_setHighScore(int value)
{

}

void MainScene::_onCheatFinishGame(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		SharedEventController::Instance().gameFinishedWithScore(100);
		_advanceToScene(ESMStoryMap);
	}
}

void MainScene::_onPauseButtonPressed(CCObject* pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		//PopupLanguage* p = new PopupLanguage;
		//SharedGameDelegate::Instance().getPopupController()->queuePopup(p);
		_advanceToScene(ESMLeaderboard);
	}
}

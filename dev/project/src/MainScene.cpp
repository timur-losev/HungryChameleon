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

MainScene::MainScene()
    : m_CellField(nullptr)
	, GameSceneBase(ESMAction)
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
	w->addWidget(r.widgetFromJsonFile("MainMenu/Background.ExportJson"));
	w->addWidget(m_topBar = r.widgetFromJsonFile("MainMenu/TopBar.ExportJson"));
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

    m_CellField = new CellField();
    assert(m_CellField->init());
    addChild(m_CellField);
	m_CellField->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(m_CellField, 0, true);
    m_CellField->setPosition(ccp(100, 100));
    m_CellField->release();
	

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
    m_CellField->onUpdate(dt);
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
		PopupLanguage* p = new PopupLanguage;
		SharedGameDelegate::Instance().getPopupController()->queuePopup(p);
	}
}

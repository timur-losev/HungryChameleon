#include "Precompiled.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"
#include "Layer3D.h"
#include "ParallaxBackground.h"
#include "System.h"

#include "Cell.h"

MainScene::MainScene()
    : m_pBackground(nullptr)
    , m_CellField(nullptr)
    , m_LabelTimer(nullptr)
    , m_MatchDuration(60000)
	, GameSceneBase(ESMAction)
{
    LoadGameSettings();

    m_QuickScrollPos = CCPointMake(-1, -1);
    m_MatchStartTime = System::GetTickCount();
}

MainScene::~MainScene()
{
    m_pBackground->removeAllChildrenWithCleanup(true);
}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();

    m_pBackground = ParallaxBackground::create();
    m_pBackground->RegisterTouchBeganCallback(std::bind(&MainScene::OnTouchBegan, this, std::placeholders::_1));
    m_pBackground->RegisterTouchMovedCallback(std::bind(&MainScene::OnTouchMoved, this, std::placeholders::_1));
    m_pBackground->RegisterTouchEndCallback(std::bind(&MainScene::OnTouchEnded, this, std::placeholders::_1));
	addChild(m_pBackground);

	IngameMenuView* igmenu = new IngameMenuView();
	igmenu->init();
	igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));
	addChild(igmenu);

#if 0
	// Counter
	m_LabelTimer = CCLabelTTF::create("Time: 1:00", "data/brookeshappelldots.ttf", 68);
	m_LabelTimer->setPosition(CCPointMake(m_LabelTimerPos.x, VisibleRect::top().y - m_LabelTimerPos.y));

	m_LabelScores = CCLabelTTF::create("Score: 0000000", "data/brookeshappelldots.ttf", 68);
	m_LabelScores->setPosition(CCPointMake(m_ScoresTimerPos.x, VisibleRect::top().y - m_ScoresTimerPos.y));

	addChild(m_LabelTimer);
	addChild(m_LabelScores);
#endif // 0

	extension::UILayer* w = extension::UILayer::create();
	extension::GUIReader r;
	w->addWidget(r.widgetFromJsonFile("MainMenu/ActionPhase.ExportJson"));
	addChild(w);


    m_CellField = new CellField();
    assert(m_CellField->init());
    addChild(m_CellField);
    m_CellField->release();
    m_CellField->setPosition(ccp(100, 100));

    /*m_BubbleSet.reset(new BubbleSet());
    m_MatrixField.reset(new MatrixField());*/

   // igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();

    schedule(schedule_selector(MainScene::onUpdate), 0.0f);
}

void MainScene::onMainMenuTap( CCObject* )
{
	_AdvanceToScene(ESMMainMenu);
}

void MainScene::OnTouchEnded(CCTouch* touch)
{
	m_CellField->onTouchReleased(touch);
}

void MainScene::OnTouchMoved(CCTouch* touch)
{
    m_CellField->onTouchMoved(touch);

    m_pBackground->Scroll(touch);
}

void MainScene::onUpdate(float dt)
{
    m_CellField->onUpdate(dt);
}

void MainScene::UpdateMatrix(float dt)
{

}

bool MainScene::LoadGameSettings()
{
    std::string fullname = System::GetBundlePath() + "data/game_settings.xml";

    TiXmlDocument doc(fullname.c_str());
    doc.LoadFile();
    TiXmlElement* root = doc.RootElement();
    if (!root)
    {
        return false;
    }

    TiXmlElement* xglobal = root->FirstChildElement("Global");
    TiXmlElement* xbubbleField = root->FirstChildElement("BubblesField");
    TiXmlElement* xtimeField = root->FirstChildElement("TimeField");
    TiXmlElement* xscoresField = root->FirstChildElement("ScoresField");
    TiXmlElement* xflyingBubbles = root->FirstChildElement("FlyingBubbles");
    if (!xglobal ||
        !xbubbleField ||
        !xtimeField ||
        !xscoresField ||
        !xflyingBubbles)
    {
        return false;
    }
    xbubbleField->Attribute("x", &m_BubbleViewDisplacement.x);
    xbubbleField->Attribute("y", &m_BubbleViewDisplacement.y);
    xbubbleField->Attribute("space_between_bubbles", &m_SpaceBetweenBubbles);
    xglobal->Attribute("duration_of_match", &m_MatchDuration);
    xtimeField->Attribute("x", &m_LabelTimerPos.x);
    xtimeField->Attribute("y", &m_LabelTimerPos.y);
    xscoresField->Attribute("x", &m_ScoresTimerPos.x);
    xscoresField->Attribute("y", &m_ScoresTimerPos.y);

    return true;
}

void MainScene::RemoveFlyingBubbles(CCNode* sender)
{

}

void MainScene::OnTouchBegan(CCTouch* touch)
{
    m_CellField->onTouchPressed(touch);
}

#include "Precompiled.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"
#include "Layer3D.h"
#include "System.h"

#include "Cell.h"

MainScene::MainScene()
    : m_CellField(nullptr)
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
}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();

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
	w->addWidget(r.widgetFromJsonFile("MainMenu/Background.ExportJson"));
	w->addWidget(r.widgetFromJsonFile("MainMenu/TopBar.ExportJson"));
	addChild(w);


    m_CellField = new CellField();
    assert(m_CellField->init());
    addChild(m_CellField);
	m_CellField->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(m_CellField, 0, true);
    m_CellField->setPosition(ccp(100, 100));
    m_CellField->release();

    /*m_BubbleSet.reset(new BubbleSet());
    m_MatrixField.reset(new MatrixField());*/

   // igmenu->release();

	
//	m_CellField->ccTouchBegan RegisterTouc
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

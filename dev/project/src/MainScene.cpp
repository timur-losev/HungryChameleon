#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"
#include "Layer3D.h"
#include "ParallaxBackground.h"
#include "BubbleElement.h"
#include "CSystem.h"

MainScene::MainScene()
	: m_pBackground(0)
	, m_LabelTimer(0)
	, m_MatchDuration(0)
{
	LoadGameSettings();

	m_QuickScrollPos = CCPointMake(-1, -1);
	m_MatchStartTime = CSystem::GetTickCount();

	BubbleElement::LoadBubbles();
}

MainScene::~MainScene()
{
	m_pBackground->removeAllChildrenWithCleanup(true);
	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			delete m_BubblesView[i][j];
		}
	}

	m_BubblesView.clear();
}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();

    m_pBackground = ParallaxBackground::create();
	m_pBackground->RegisterTouchBeganCallback(std::bind(&MainScene::OnTouchEnded, this, std::placeholders::_1));
	m_pBackground->RegisterTouchMovedCallback(std::bind(&MainScene::OnTouchMoved, this, std::placeholders::_1));

    IngameMenuView* igmenu = new IngameMenuView();
    igmenu->init();
	igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));

	// Counter
	m_LabelTimer = CCLabelTTF::create("Time: 1:00", "data/brookeshappelldots.ttf", 68);
	m_LabelTimer->setPosition(CCPointMake(m_LabelTimerPos.x, VisibleRect::top().y - m_LabelTimerPos.y));

	m_LabelScores = CCLabelTTF::create("Score: 0000000", "data/brookeshappelldots.ttf", 68);
	m_LabelScores->setPosition(CCPointMake(m_ScoresTimerPos.x, VisibleRect::top().y - m_ScoresTimerPos.y));
		
	addChild(m_pBackground);
    addChild(igmenu);
	addChild(m_LabelTimer);
	addChild(m_LabelScores);

	igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();

	m_ScoresCount = 0;

	m_MatrixField.GenerateField();
	std::vector<CCSprite*> line;
	line.resize(MatrixField::GetMaxVisible());

	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			BubbleElement* element;
			int x = m_BubbleViewDisplacement.x + i * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			int y = VisibleRect::top().y - m_BubbleViewDisplacement.y - BubbleElement::GetBubbleSize() - j * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			
			element = new BubbleElement( m_MatrixField.GetVisible(i, j) );//rand() % MatrixField::GetMaxTypes() );
			element->retain();
			element->setPosition( ccp( x, y ) );

			m_pBackground->addChild(element);
			line[j] = element;
		}

		m_BubblesView.push_back(line);
	}

	schedule(schedule_selector(MainScene::onUpdate), 0.0f);
}

void MainScene::onMainMenuTap( CCObject* )
{
    GameDelegate::sharedGameDelegate()->returnToMainMenu();
}

void MainScene::OnTouchEnded(CCTouch* touch)
{
	int direction;
	if (abs(m_QuickScrollDelta.x) > abs(m_QuickScrollDelta.y))
	{
		direction = (m_QuickScrollDelta.x >= 0) ? -2 : -1;
	}
	else
	{
		direction = (m_QuickScrollDelta.y >= 0) ? 0 : 1;
	}

	m_MatrixField.Scroll(direction, m_QuickScrollPos.x, m_QuickScrollPos.y);
	m_QuickScrollPos = CCPointMake(-1, -1);
}

void MainScene::OnTouchMoved(CCTouch* touch)
{
	CCPoint delta = touch->getDelta();
	CCPoint position = touch->getLocationInView();
	int fieldSizeX = m_BubbleViewDisplacement.x + MatrixField::GetMaxVisible() * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
    int fieldSizeY = m_BubbleViewDisplacement.y + MatrixField::GetMaxVisible() * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);

	if (position.x < m_BubbleViewDisplacement.x || 
		position.y < m_BubbleViewDisplacement.y ||
		position.x >= fieldSizeX || 
		position.y >= fieldSizeY ||
		(delta.x == 0 && delta.y == 0))
	{
        // Scroll parallax background
        m_pBackground->Scroll(touch);
		return;
	}

	position.x -= m_BubbleViewDisplacement.x;
	position.y -= m_BubbleViewDisplacement.y;

	int yPos = (int)(position.x / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));
	int xPos = (int)(position.y / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));

	if (m_QuickScrollPos.x == -1 && m_QuickScrollPos.y == -1)
	{
		m_QuickScrollPos	= CCPointMake(xPos, yPos);
		m_QuickScrollVertical = abs(delta.x) > abs(delta.y);
	}

	if (m_QuickScrollVertical)
	{
		delta.y = 0;
		delta.x = (BubbleElement::GetBubbleSize() * ((delta.x >= 0) ? 1.0f : -1.0f)) / 2.0f;
	}
	else
	{
		delta.x = 0;
		delta.y = (BubbleElement::GetBubbleSize() * ((delta.y >= 0) ? 1.0f : -1.0f)) / 2.0f;
	}
		
	m_QuickScrollDelta = delta;
}

void MainScene::onUpdate(float dt)
{
	unsigned int currentTime = CSystem::GetTickCount() / 1000;
	if (currentTime < m_MatchStartTime / 1000 + m_MatchDuration)
	{
		int timeLeft = (int)(m_MatchStartTime / 1000 + m_MatchDuration - currentTime);
		int hour = timeLeft / 60;
		int sec =  (timeLeft - (hour * 60));

		char strTime[64];
		sprintf(strTime, "Time: %d:%.2d", hour, sec);
		m_LabelTimer->setString(strTime);
	}
	else
	{
		// Game Over
		GameDelegate::sharedGameDelegate()->returnToMainMenu();
	}

	UpdateMatrix(dt);
	
	static bool needMatrixScroll = false;
	static unsigned long lastTimeUpdateMatrix = CSystem::GetTickCount();
	if (CSystem::GetTickCount() - lastTimeUpdateMatrix > 250)
	{
		lastTimeUpdateMatrix = CSystem::GetTickCount();

		MatchesList_t matches = m_MatrixField.GetFirstMatches();
		if (matches.empty() && needMatrixScroll)
		{
			m_MatrixField.ScrollDown();
		}
		else if (!matches.empty() && !needMatrixScroll)
		{
			needMatrixScroll = true;
		}

		m_ScoresCount += matches.size() * 50;
		
		char strScore[128];
		sprintf(strScore, "Score: %.7d", m_ScoresCount);
		m_LabelScores->setString(strScore);
	}
}

void MainScene::UpdateMatrix(float dt)
{
	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			BubbleElement* element = static_cast<BubbleElement*>(m_BubblesView[i][j]);
			
			int type = m_MatrixField.GetVisible(i, j);
			if (type >= 0)
			{
				element->SetType(type);
				element->setVisible(true);
				element->setOpacity(255);
			}
			else
			{
				//element->setVisible(false);
				element->setOpacity(128);
			}

			// additional shift for row or column
			int x = m_BubbleViewDisplacement.x + i * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			int y = VisibleRect::top().y - m_BubbleViewDisplacement.y - BubbleElement::GetBubbleSize() - j * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);

			if ((i == m_QuickScrollPos.y && !m_QuickScrollVertical) || (j == m_QuickScrollPos.x && m_QuickScrollVertical))
			{
				x += m_QuickScrollDelta.x;
				y += m_QuickScrollDelta.y;
			}

			element->setPosition( ccp( x, y ) );

			element->Update(dt);
		}
	}	
}

bool MainScene::LoadGameSettings()
{
	std::string fullname = CSystem::GetBundlePath() + "data/game_settings.xml";

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
	if (!xglobal ||
		!xbubbleField ||
		!xtimeField ||
		!xscoresField)
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
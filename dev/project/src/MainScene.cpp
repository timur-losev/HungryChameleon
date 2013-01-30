#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"
#include "Layer3D.h"
#include "ParallaxBackground.h"
#include "BubbleElement.h"
#include "CSystem.h"

int MainScene::m_BubbleViewDisplacement		= 40;
int	MainScene::m_SpaceBetweenBubbles		= 5;

MainScene::MainScene()
	: m_pBackground(0)
{
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
    
    addChild(m_pBackground);
    addChild(igmenu);

    igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));

    igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();

	m_MatrixField.GenerateField();
	std::vector<CCSprite*> line;
	line.resize(MatrixField::GetMaxVisible());

	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			BubbleElement* element;
			int x = m_BubbleViewDisplacement + i * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			int y = VisibleRect::top().y - m_BubbleViewDisplacement - BubbleElement::GetBubbleSize() - j * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			
			element = new BubbleElement( m_MatrixField.GetVisible(i, j) );//rand() % MatrixField::GetMaxTypes() );
			element->retain();
			element->setPosition( ccp( x, y ) );

			m_pBackground->addChild(element);
			line[j] = element;
		}

		m_BubblesView.push_back(line);
	}

	schedule(schedule_selector(MainScene::onUpdate), 0.1f);
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
	int fieldSize = m_BubbleViewDisplacement + MatrixField::GetMaxVisible() * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);

	if (position.x < m_BubbleViewDisplacement || 
		position.y < m_BubbleViewDisplacement ||
		position.x >= fieldSize || 
		position.y >= fieldSize ||
		(delta.x == 0 && delta.y == 0))
	{
		return;
	}

	// Scroll parallax background
	//m_pBackground->Scroll(delta.x);

	position.x -= m_BubbleViewDisplacement;
	position.y -= m_BubbleViewDisplacement;

	int yPos = (int)(position.x / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));
	int xPos = (int)(position.y / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));

	if (abs(delta.x) > abs(delta.y))
	{
		m_QuickScrollVertical = true;

		delta.y = 0;
		delta.x = (delta.x < BubbleElement::GetBubbleSize()) ? (BubbleElement::GetBubbleSize() * ((delta.x >= 0) ? 1.0f : -1.0f)) / 2.0f : delta.x;
	}
	else
	{
		m_QuickScrollVertical = false;
		delta.x = 0;
		delta.y = (delta.y < BubbleElement::GetBubbleSize()) ? (BubbleElement::GetBubbleSize() * ((delta.y >= 0) ? 1.0f : -1.0f)) / 2.0f : delta.y;
	}

	m_QuickScrollPos	= CCPointMake(xPos, yPos);
	m_QuickScrollDelta	= CCPointMake(delta.x, delta.y);
}

void MainScene::onUpdate(float dt)
{
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
			int x = m_BubbleViewDisplacement + i * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			int y = VisibleRect::top().y - m_BubbleViewDisplacement - BubbleElement::GetBubbleSize() - j * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);

			if ((i == m_QuickScrollPos.y && !m_QuickScrollVertical) || (j == m_QuickScrollPos.x && m_QuickScrollVertical))
			{
				x += m_QuickScrollDelta.x;
				y += m_QuickScrollDelta.y;
			}

			element->setPosition( ccp( x, y ) );
		}
	}	
}
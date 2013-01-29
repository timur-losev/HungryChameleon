#include "GameScene.h"
#include "GameView.h"
#include "VisibleRect.h"
#include "BubbleElement.h"
#include "CSystem.h"

int GameScene::m_BubbleViewDisplacement		= 40;
int	GameScene::m_SpaceBetweenBubbles		= 5;

GameScene::GameScene()
{
	BubbleElement::FakeBubblesInit();
}

GameScene::~GameScene()
{
	m_pGameView->removeAllChildrenWithCleanup(true);
	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			delete m_BubblesView[i][j];
		}
	}

	m_BubblesView.clear();
}

void GameScene::onEnter()
{
    CCScene::onEnter();

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

			m_pGameView->addChild(element);
			line[j] = element;
		}

		m_BubblesView.push_back(line);
	}

	schedule(schedule_selector(GameScene::onUpdate), 0.1f);
}

void GameScene::createInstance()
{
    m_pGameView = new GameView();

    addChild(m_pGameView);
    m_pGameView->autorelease();
	m_pGameView->RegisterTouchBeganCallback(std::bind(&GameScene::OnTouchEnded, this, std::placeholders::_1));
	m_pGameView->RegisterTouchMovedCallback(std::bind(&GameScene::OnTouchMoved, this, std::placeholders::_1));
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void GameScene::OnTouchEnded(CCTouch* touch)
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

void GameScene::OnTouchMoved(CCTouch* touch)
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

void GameScene::onUpdate(float dt)
{
	UpdateMatrix(dt);
	
	static bool needMatrixScroll = false;
	static unsigned long lastTimeUpdateMatrix = CSystem::GetTickCount();
	if (CSystem::GetTickCount() - lastTimeUpdateMatrix > 500)
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

void GameScene::UpdateMatrix(float dt)
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
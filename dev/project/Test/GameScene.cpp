#include "GameScene.h"
#include "GameView.h"
#include "VisibleRect.h"
#include "BubbleElement.h"

GameScene::GameScene()
	: m_State(eIdle)
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
			int x = m_BubbleViewDispl + i * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			int y = VisibleRect::top().y - m_BubbleViewDispl - BubbleElement::GetBubbleSize() - j * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);
			
			element = new BubbleElement( m_MatrixField.GetVisible(i, j) );//rand() % MatrixField::GetMaxTypes() );
			element->retain();
			element->setPosition( ccp( x, y ) );

			m_pGameView->addChild(element);
			line[j] = element;
		}

		m_BubblesView.push_back(line);
	}

	schedule(schedule_selector(GameScene::onUpdate), 0.5f);
}

void GameScene::createInstance()
{
    m_pGameView = new GameView();

    addChild(m_pGameView);
    m_pGameView->autorelease();
	m_pGameView->RegisterTouchCallback(std::bind(&GameScene::OnTouchBegan, this, std::placeholders::_1));
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void GameScene::OnTouchBegan(CCTouch* touch)
{
	CCPoint delta = touch->getDelta();
	CCPoint position = touch->getLocationInView();
	int fieldSize = m_BubbleViewDispl + MatrixField::GetMaxVisible() * (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles);

	if (position.x < m_BubbleViewDispl || 
		position.y < m_BubbleViewDispl ||
		position.x >= fieldSize || 
		position.y >= fieldSize)
	{
		return;
	}

	position.x -= m_BubbleViewDispl;
	position.y -= m_BubbleViewDispl;

	int yPos = (int)(position.x / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));
	int xPos = (int)(position.y / (BubbleElement::GetBubbleSize() + m_SpaceBetweenBubbles));
	int direction;

	if (abs(delta.x) > abs(delta.y))
	{
		direction = (delta.x >= 0) ? -2 : -1;
	}
	else
	{
		direction = (delta.y >= 0) ? 0 : 1;
	}

	m_MatrixField.Scroll(direction, xPos, yPos);

	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			BubbleElement* element = static_cast<BubbleElement*>(m_BubblesView[i][j]);
			element->SetType(m_MatrixField.GetVisible(i, j));
		}
	}
}

bool GameScene::DoScroll(const CCRect region)
{
	return true;
}

void GameScene::onUpdate(float dt)
{
	switch (m_State)
	{
	case eWaitBoomAnim:
	{
		for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
		{
			for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
			{
				BubbleElement* element = static_cast<BubbleElement*>(m_BubblesView[i][j]);
				element->SetType(m_MatrixField.GetVisible(i, j));
				element->setVisible(true);
			}
		}	

		m_State = eIdle;	
	}
	break;
	case eIdle:
	{
		MatchesList_t matches = m_MatrixField.GetFirstMatches();

		while (!matches.empty())
		{
			BubbleElement* element = static_cast<BubbleElement*>(m_BubblesView[(int)matches[0].y][(int)matches[0].x]);
			element->setVisible(false);//SetType(MatrixField::GetMaxTypes() + 1);
			matches.erase(matches.begin());

			m_State = eWaitBoomAnim;
		}
	}
	break;
	default:
		break;
	};
}

void GameScene::onUpdateMatrix(float dt)
{
	
}
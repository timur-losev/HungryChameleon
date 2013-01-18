#include "GameScene.h"
#include "GameView.h"
#include "VisibleRect.h"
#include "BubbleElement.h"

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
			const int space = 5;
			const int shift = 40;
			int x = shift + i * (BubbleElement::GetBubbleSize() + space);
			int y = VisibleRect::top().y - shift - j * (BubbleElement::GetBubbleSize() + space);
			
			element = new BubbleElement( rand() % MatrixField::GetMaxTypes() );
			element->retain();
			element->setPosition( ccp( x, y ) );

			m_pGameView->addChild(element);
			line[j] = element;
		}

		m_BubblesView.push_back(line);
	}
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
	for(int i = 0; i < MatrixField::GetMaxVisible(); ++i)
	{
		for(int j = 0; j < MatrixField::GetMaxVisible(); ++j)
		{
			BubbleElement* element = static_cast<BubbleElement*>(m_BubblesView[i][j]);
			element->SetType(m_MatrixField.GetVisible(i, j));
		}
	}
}
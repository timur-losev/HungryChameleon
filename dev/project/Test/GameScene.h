#pragma once
#include <cocos2d.h>
using namespace cocos2d;

#include "MatrixField.h"

class GameView;

class GameScene : public CCScene
{
private:
	static const int			m_BubbleViewDispl		= 40;
	static const int			m_SpaceBetweenBubbles	= 5;

	GameView*					m_pGameView;
	MatrixField					m_MatrixField;
	std::vector< std::vector<CCSprite*> >   m_BubblesView;


	void OnTouchBegan(CCTouch* touch);
	void onUpdate(float dt);
	void onUpdateMatrix(float dt);
protected:
public:
    GameScene();
    virtual ~GameScene();

    virtual void onEnter();
    virtual void createInstance();
	bool DoScroll(const CCRect region);
};
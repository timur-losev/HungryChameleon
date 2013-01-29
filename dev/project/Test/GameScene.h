#pragma once
#include <cocos2d.h>
using namespace cocos2d;

#include "MatrixField.h"

class GameView;

class GameScene : public CCScene
{
private:
	static int			m_BubbleViewDisplacement;
	static int			m_SpaceBetweenBubbles;

	GameView*					m_pGameView;
	MatrixField					m_MatrixField;
	std::vector< std::vector<CCSprite*> >   m_BubblesView;
	CCPoint						m_QuickScrollPos;
	CCPoint						m_QuickScrollDelta;
	bool						m_QuickScrollVertical;


	void OnTouchEnded(CCTouch* touch);
	void OnTouchMoved(CCTouch* touch);
	void onUpdate(float dt);
	void UpdateMatrix(float dt);
protected:
public:
    GameScene();
    virtual ~GameScene();

    virtual void onEnter();
    virtual void createInstance();
};
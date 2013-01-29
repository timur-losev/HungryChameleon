#pragma once

#include "GameSceneBase.h"
#include "MatrixField.h"

class ParallaxBackground;

class MainScene: public GameSceneBase
{
private:
    ParallaxBackground*					m_pBackground;

	static int					m_BubbleViewDisplacement;
	static int					m_SpaceBetweenBubbles;

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
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void                    onMainMenuTap(CCObject*);
};
#pragma once

#include "GameSceneBase.h"
#include "MatrixField.h"

class ParallaxBackground;

class MainScene: public GameSceneBase
{
private:
    ParallaxBackground*			m_pBackground;

	CCPoint						m_BubbleViewDisplacement;
	int							m_SpaceBetweenBubbles;

	MatrixField					m_MatrixField;
	std::vector< std::vector<CCSprite*> >   m_BubblesView;
	CCPoint						m_QuickScrollPos;
	CCPoint						m_QuickScrollDelta;
	bool						m_QuickScrollVertical;

	// Timer
	int							m_MatchDuration;
	unsigned long				m_MatchStartTime;
	CCLabelTTF*					m_LabelTimer;
	CCPoint						m_LabelTimerPos;

	// Scores
	int							m_ScoresCount;
	CCLabelTTF*					m_LabelScores;
	CCPoint						m_ScoresTimerPos;


	void OnTouchEnded(CCTouch* touch);
	void OnTouchMoved(CCTouch* touch);
	void onUpdate(float dt);
	void UpdateMatrix(float dt);
	bool LoadGameSettings();

protected:
public:
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void                    onMainMenuTap(CCObject*);
};
#pragma once

#include "GameSceneBase.h"

class CellField;

class MainScene: public GameSceneBase
{
private:
    CellField*                  m_CellField;

    CCPoint						m_BubbleViewDisplacement;
    int							m_SpaceBetweenBubbles;


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

    void OnTouchBegan(CCTouch* touch);
    void OnTouchEnded(CCTouch* touch);
    void OnTouchMoved(CCTouch* touch);
    void onUpdate(float dt);
    void UpdateMatrix(float dt);
    bool LoadGameSettings();

	extension::UIWidget*		m_topBar = nullptr;

	void _setScore(int value);
	void _setCash(int value);
	void _setHighScore(int value);

protected:
public:
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void					PushFlyingBubbles(const std::vector<CCPoint>& bubbles);
    void					RemoveFlyingBubbles(CCNode* sender);

    void                    onMainMenuTap(CCObject*);
};
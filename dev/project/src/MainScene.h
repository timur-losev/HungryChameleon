#pragma once

#include "GameSceneBase.h"

class MainScene: public GameSceneBase
{
public:
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void					PushFlyingBubbles(const std::vector<CCPoint>& bubbles);
    void					RemoveFlyingBubbles(CCNode* sender);

	void					onEnterTransitionDidFinish();
	
	void                    onMainMenuTap(CCObject*);
	void					tickTimer(float = 0.0f);

protected:
	void					_onUpdate(float dt);

private:
	extension::UIWidget*	m_topBar = nullptr;

	void					_setScore(int value);
	void					_setCash(int value);
	void					_setHighScore(int value);

	void					_onCheatFinishGame(CCObject * pSender, extension::TouchEventType ev);
	void					_onPauseButtonPressed(CCObject* pSender, extension::TouchEventType ev);

	void					_startTimer();
	void					_pauseTimer();
	void					_unpauseTimer();
	void					_updateTimerValue(const char*);

private:
	extension::UILabel*		m_labelTimer = nullptr;
	float					m_levelTimeTotal = 0;
	float					m_levelTimeLeft = 0;
};
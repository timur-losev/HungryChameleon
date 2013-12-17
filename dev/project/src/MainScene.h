#pragma once

#include "GameSceneBase.h"

class CellField;

class MainScene: public GameSceneBase
{
private:
    CellField*                  m_CellField;
	
	extension::UIWidget*		m_topBar = nullptr;

	void					_setScore(int value);
	void					_setCash(int value);
	void					_setHighScore(int value);

	void					_onCheatFinishGame(CCObject * pSender, extension::TouchEventType ev);
	void					_onPauseButtonPressed(CCObject* pSender, extension::TouchEventType ev);

protected:
	void					_onUpdate(float dt);
public:
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void					PushFlyingBubbles(const std::vector<CCPoint>& bubbles);
    void					RemoveFlyingBubbles(CCNode* sender);

    void                    onMainMenuTap(CCObject*);
};
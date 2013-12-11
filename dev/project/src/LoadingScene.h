#pragma once

#include "GameSceneBase.h"
#include "SceneModes.h"

class SceneController;

class LoadingScene : public GameSceneBase
{
private:

    void _onTouchBegan(CCTouch* touch);
    void _onTouchEnded(CCTouch* touch);
    void _onTouchMoved(CCTouch* touch);
    void _updateMatrix(float dt);
    bool _loadGameSettings();
	bool _loadResources();

	enum ELoadingStep
	{
		ELoadingAnimations = 0,
		ELoadingSave,
		ELoadingTexts,

		ETotalSteps
	}	m_step;

protected:
	void					_onUpdate(float dt);

public:
	LoadingScene();
	~LoadingScene();

    bool                    init();
    virtual void            onEnter();

    void					PushFlyingBubbles(const std::vector<CCPoint>& bubbles);
    void					RemoveFlyingBubbles(CCNode* sender);

    void                    onMainMenuTap(CCObject*);
};
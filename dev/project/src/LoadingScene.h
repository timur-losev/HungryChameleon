#pragma once

#include "GameSceneBase.h"
#include "SceneModes.h"

class SceneController;

class LoadingScene : public GameSceneBase
{
private:

    void OnTouchBegan(CCTouch* touch);
    void OnTouchEnded(CCTouch* touch);
    void OnTouchMoved(CCTouch* touch);
    void onUpdate(float dt);
    void UpdateMatrix(float dt);
    bool LoadGameSettings();

protected:
public:
	LoadingScene();
	~LoadingScene();

    bool                    init();
    virtual void            onEnter();

    void					PushFlyingBubbles(const std::vector<CCPoint>& bubbles);
    void					RemoveFlyingBubbles(CCNode* sender);

    void                    onMainMenuTap(CCObject*);
};
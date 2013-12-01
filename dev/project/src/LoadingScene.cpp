#include "Precompiled.h"
#include "LoadingScene.h"

#include "SceneController.h"
#include "TextManager.h"

LoadingScene::LoadingScene()
	:GameSceneBase(ESMLoading)
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::init()
{
	return true;
}

void LoadingScene::onEnter()
{
    GameSceneBase::onEnter();
	//SharedTextManager::Instance().loadLanguage(TextManager::s_English);
	SharedTextManager::Instance().loadLanguage(TextManager::s_Russian);

	schedule(schedule_selector(LoadingScene::onUpdate), 0.0f);
}

void LoadingScene::onMainMenuTap(CCObject*)
{
}

void LoadingScene::OnTouchEnded(CCTouch* touch)
{
}


void LoadingScene::OnTouchMoved(CCTouch* touch)
{
}

void LoadingScene::onUpdate(float dt)
{
	_AdvanceToScene(ESMMainMenu);
}

void LoadingScene::OnTouchBegan(CCTouch* touch)
{
}

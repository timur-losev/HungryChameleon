#include "Precompiled.h"
#include "SceneController.h"
#include "GameSceneBase.h"

#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "MainScene.h"

SceneController::SceneController()
{

}

SceneController::~SceneController()
{

}

void SceneController::AdvanceToMode(ESceneModes mode)
{
	m_sceneMode = _CreateScene(mode);
	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5f, m_sceneMode));
}

void SceneController::EnterSubMode(ESceneSubmodes submode)
{

}

void SceneController::ExitSubmode()
{

}

void SceneController::Launch()
{
	if (m_sceneMode)
		return;

	m_sceneMode = _CreateScene(ESMLoading);
	CCDirector::sharedDirector()->runWithScene(m_sceneMode);
	m_sceneMode->release();
}

GameSceneBase* SceneController::_CreateScene(ESceneModes mode)
{
	GameSceneBase* ret = nullptr;
	switch (mode)
	{
	case ESMLoading:
		ret = new LoadingScene;
		break;
	case ESMMainMenu:
		ret = new MainMenuScene;
		break;
	case ESMAction:
		ret = new MainScene;
		break;
	default:
		break;
	}
	
	if (ret && ret->init())
	{
		//ret->init();
		ret->AddSceneSlots(this);
	}
	return ret;
}
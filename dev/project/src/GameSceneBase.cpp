#include "Precompiled.h"
#include "GameSceneBase.h"
#include "SceneController.h"

GameSceneBase::GameSceneBase(ESceneModes mode)
	:m_baseSceneMode(mode)
{

}

GameSceneBase::~GameSceneBase()
{

}

void GameSceneBase::onEnter()
{
    CCScene::onEnter();
}

void GameSceneBase::AddSceneSlots(SceneController* scene)
{
	m_signalChangeScene.connect(scene, &SceneController::AdvanceToMode);
}
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
	_AdvanceToScene.connect(scene, &SceneController::AdvanceToMode);
}
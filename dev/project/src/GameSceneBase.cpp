#include "Precompiled.h"
#include "GameSceneBase.h"
#include "SceneController.h"

GameSceneBase::GameSceneBase(ESceneModes mode)
	: m_baseSceneMode(mode)
{
	this->scheduleUpdate();
}

GameSceneBase::~GameSceneBase()
{

}

void GameSceneBase::onEnter()
{
    CCScene::onEnter();
}

void GameSceneBase::addSceneSlots(SceneController* scene)
{
	_advanceToScene.connect(scene, &SceneController::advanceToMode);
}

void GameSceneBase::update(float dt)
{
	if (isPaused())
		return;
	_onUpdate(dt);
}

void GameSceneBase::setPaused(bool value)
{
	m_baseIsPaused = value; 
}

bool GameSceneBase::isPaused() const
{
	return m_baseIsPaused;
}

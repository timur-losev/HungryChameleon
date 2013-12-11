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

void GameSceneBase::reloadLanguage()
{
	CCArray* children = getChildren();
	CCObject* child;
	CCARRAY_FOREACH(children, child)
	{
		extension::UILabel* pText = dynamic_cast<extension::UILabel*>(child);
		if (pText)
		{
			pText->setText("changed");
		}
	}
}

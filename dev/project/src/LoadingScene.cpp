#include "Precompiled.h"
#include "LoadingScene.h"

#include "SceneController.h"
#include "GameDelegate.h"
#include "SaveController.h"
#include "EventController.h"
#include "TextManager.h"
#include "Player.h"

LoadingScene::LoadingScene()
	: GameSceneBase(ESMLoading)
	, m_step(ELoadingAnimations)
{
	SharedTextManager::Instance();
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
}

void LoadingScene::onMainMenuTap(CCObject*)
{
}

void LoadingScene::_onTouchEnded(CCTouch* touch)
{
}

void LoadingScene::_onTouchMoved(CCTouch* touch)
{
}

void LoadingScene::_onUpdate(float dt)
{
	if (_loadResources())
	{
		_advanceToScene(ESMMainMenu);
	}
}

void LoadingScene::_onTouchBegan(CCTouch* touch)
{
}

bool LoadingScene::_loadResources()
{
	switch (m_step)
	{
	case ELoadingAnimations:
		extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("anim/spider.ExportJson");
		break;
	case ELoadingSave:
		GameDelegate::getSaveController()->load();
		GameDelegate::getPlayer()->readSave();
		break;
	case ELoadingTexts:
		SharedEventController::Instance().changeLanguage(GameDelegate::getSaveController()->getLanguage());
		break;
	default:
		break;
	}
	m_step = ELoadingStep(((int)m_step)+1);

	return (m_step >= ETotalSteps);
}
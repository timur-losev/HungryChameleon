#include "Precompiled.h"
#include "LoadingScene.h"

#include "SceneController.h"
#include "GameDelegate.h"
#include "SaveController.h"
#include "EventController.h"
#include "TextManager.h"

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
	schedule(schedule_selector(LoadingScene::_onUpdate), 0.0f);
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
		_AdvanceToScene(ESMMainMenu);
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
		extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("data/anim/spider.ExportJson");
		break;
	case ELoadingSave:
		SharedGameDelegate::Instance().getSaveController()->load();
		break;
	case ELoadingTexts:
		SharedEventController::Instance().ChangeLanguage(SharedGameDelegate::Instance().getSaveController()->getLanguage());
		break;
	default:
		break;
	}
	m_step = ELoadingStep(((int)m_step)+1);

	return (m_step >= ETotalSteps);
}
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
	extension::UILayer* w = extension::UILayer::create();
	extension::GUIReader r;
	w->addWidget(r.widgetFromJsonFile("LoadingScreen/LoadingScreen.ExportJson"));
	addChild(w);
	extension::UIWidget* placeholder = w->getWidgetByName("placeholder");
	if (placeholder)
	{
		extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("anim/LoadingCircle.ExportJson");
		extension::CCArmature *armature = extension::CCArmature::create("LoadingCircle");
		armature->getAnimation()->playByIndex(0);
		armature->setAnchorPoint(ccp(0, 0));
		armature->setScale(2);
		armature->setPosition(placeholder->getPosition());
		addChild(armature, 2);
	}
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
		m_advanceToScene(ESMStoryMap);
		setPaused(true);
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
	{;
		extension::CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("anim/spider.ExportJson");
		break;
	}
	case ELoadingSave:
		SharedGameDelegate::Instance().getPlayer()->readSave();
		break;
	case ELoadingTexts:
	{
		std::string lang = SharedGameDelegate::Instance().getSaveController()->getLanguage();
		if (lang.empty())
		{
			lang = TextManager::s_English;
		}
		SharedEventController::Instance().changeLanguage(lang);
	}
		break;
	default:
		break;
	}
	m_step = ELoadingStep(((int)m_step)+1);

	return (m_step >= ETotalSteps);
}
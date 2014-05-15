#include "Precompiled.h"
#include "SceneController.h"
#include "GameSceneBase.h"

#include "LoadingScene.h"
#include "MainMenuScene.h"
#include "MainScene.h"
#include "StoryMapScene.h"
#include "LeaderboardScene.h"

#include "PopupBase.h"
#include "EventController.h"

SceneController::SceneController()
{
    SharedEventController::Instance().popupClosed.connect(this, &SceneController::_onPopupClosed);
    SharedEventController::Instance().changeLanguage.connect(this, &SceneController::_onLanguageChanged);

#ifdef DEBUG
    //CCDirector::sharedDirector()->getKeypadDispatcher()->addDelegate

#endif


}

SceneController::~SceneController()
{
}

void SceneController::advanceToMode(ESceneModes mode)
{
    GameSceneBase* sceneMode = _createScene(mode);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeTR::create(0.5f, sceneMode));
}

GameSceneBase* SceneController::_currentScene()
{
    return dynamic_cast<GameSceneBase*>(CCDirector::sharedDirector()->getRunningScene());
}

void SceneController::addPopup(PopupBase* popup)
{
    GameSceneBase* sceneMode = _currentScene();
    sceneMode->setPaused(true);
    sceneMode->addChild(popup);
}

void SceneController::launch()
{
    if (_currentScene())
        return;

    GameSceneBase* sceneMode = _createScene(ESMLoading);
    sceneMode->release();
    CCDirector::sharedDirector()->runWithScene(sceneMode);
}

GameSceneBase* SceneController::_createScene(ESceneModes mode)
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
    case ESMStoryMap:
        ret = new StoryMapScene;
        break;
    case ESMLeaderboard:
        ret = new LeaderboardScene;
        break;
    default:
        break;
    }

    if (ret && ret->init())
    {
        ret->addSceneSlots(this);
        return ret;
    }
    return nullptr;
}

bool SceneController::canShowPopup()
{
    if (!_currentScene())
        return false;
    return _currentScene()->canShowPopup();
}

void SceneController::_onPopupClosed()
{
    _currentScene()->setPaused(false);
}

void SceneController::_onLanguageChanged(const std::string&)
{
    _currentScene()->reloadLanguage();
}

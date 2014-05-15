#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "SceneController.h"
#include "SaveController.h"
#include "Player.h"
#include "PopupController.h"
#include "FileUtils.h"
#include "LevelSettingsController.h"
#include "OnlineController.h"

GameDelegate::GameDelegate()
{
    // Create the appropriate instance of file utils
    FileUtils::sharedFileUtils();
    m_sceneController = new SceneController();
    m_saveController = new SaveController();
    m_player = new Player();
    m_popupController = new PopupController();
    m_levelSettingsController = new LevelSettingsController();
    m_onlineController = new OnlineController();
}

GameDelegate::~GameDelegate()
{
    delete m_player;
    delete m_popupController;
    delete m_sceneController;
    delete m_saveController;
    delete FileUtils::sharedFileUtils();
    delete m_levelSettingsController;
    delete m_onlineController;
}

void GameDelegate::init()
{

}

void GameDelegate::startGame()
{
    m_sceneController->launch();
}

SaveController* GameDelegate::getSaveController()
{
    return SharedGameDelegate::Instance().m_saveController;
}

void GameDelegate::saveNow()
{
}

SceneController* GameDelegate::getSceneController()
{
    return SharedGameDelegate::Instance().m_sceneController;
}

Player* GameDelegate::getPlayer()
{
    return SharedGameDelegate::Instance().m_player;
}

PopupController* GameDelegate::getPopupController()
{
    return SharedGameDelegate::Instance().m_popupController;
}

LevelSettingsController* GameDelegate::getLevelSettingsController()
{
    return SharedGameDelegate::Instance().m_levelSettingsController;
}

OnlineController* GameDelegate::getOnlineController()
{
    return SharedGameDelegate::Instance().m_onlineController;
}

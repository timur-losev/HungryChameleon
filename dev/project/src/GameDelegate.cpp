#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "SceneController.h"
#include "SaveController.h"
#include "Player.h"
#include "PopupController.h"
#include "FileUtils.h"

GameDelegate::GameDelegate()
{
	m_sceneController = new SceneController;

	m_saveController = SaveController::createController();
	m_saveController->retain();

	m_player = new Player;

	m_popupController = new PopupController;
	FileUtils::sharedFileUtils();
}

GameDelegate::~GameDelegate()
{
	delete m_player;
	delete m_popupController;
	delete m_sceneController;
	delete FileUtils::sharedFileUtils();
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
	m_saveController->save();
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


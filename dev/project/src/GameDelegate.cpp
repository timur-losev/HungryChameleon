#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "SceneController.h"
#include "SaveController.h"
#include "Player.h"

GameDelegate::GameDelegate()
{
	m_sceneController = new SceneController();
	m_saveController = SaveController::createController();
	m_saveController->retain();
	m_player = new Player();
}

GameDelegate::~GameDelegate()
{
	delete m_sceneController;
	delete m_player;
}

void GameDelegate::init()
{

}

void GameDelegate::startGame()
{
	m_sceneController->Launch();
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


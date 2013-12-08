#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "SceneController.h"
#include "SaveController.h"

GameDelegate::GameDelegate()
{
	m_sceneController = new SceneController();
	m_saveController = SaveController::createController();
}

GameDelegate::~GameDelegate()
{
	delete m_sceneController;
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
	return m_saveController;
}

void GameDelegate::saveNow()
{
	m_saveController->save();
}

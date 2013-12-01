#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "SceneController.h"

GameDelegate::GameDelegate()
{
	m_sceneController = new SceneController();
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

    //MainScene* scene = new MainScene();
    //scene->init();

    //CCDirector::sharedDirector()->replaceScene( CCTransitionFadeTR::create(0.8f, scene) );
    //scene->release();
}
#if 0

void GameDelegate::openMainMenu()
{
	MainMenuScene* mmscene = new MainMenuScene();
	mmscene->init();

	CCDirector::sharedDirector()->runWithScene(mmscene);
	mmscene->release();
}

void GameDelegate::returnToMainMenu()
{
	MainMenuScene* mmscene = new MainMenuScene();
	mmscene->init(true);

	CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8f, mmscene));
	mmscene->release();
}

void GameDelegate::returnToGame()
{
	CCDirector::sharedDirector()->popScene();
}

#endif // 0

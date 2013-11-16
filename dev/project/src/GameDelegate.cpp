#include "Precompiled.h"
#include "GameDelegate.h"
#include "MainScene.h"
#include "MainMenuScene.h"

GameDelegate::GameDelegate()
{
}

GameDelegate::~GameDelegate()
{

}

void GameDelegate::init()
{

}

void GameDelegate::startGame()
{
    MainScene* scene = new MainScene();
    scene->init();

    CCDirector::sharedDirector()->replaceScene( CCTransitionFadeTR::create(0.8f, scene) );
    scene->release();
}

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

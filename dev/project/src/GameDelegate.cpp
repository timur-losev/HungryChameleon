#include "pch.h"
#include "GameDelegate.h"
#include "MainScene.h"

GameDelegate* GameDelegate::s_SharedGameDelegate = nullptr;

GameDelegate::GameDelegate()
{

}

GameDelegate::~GameDelegate()
{

}

GameDelegate* GameDelegate::sharedGameDelegate()
{
    if ( !s_SharedGameDelegate )
    {
        s_SharedGameDelegate = new GameDelegate();
        s_SharedGameDelegate->init();
    }

    return s_SharedGameDelegate;
}

void GameDelegate::init()
{

}

void GameDelegate::startGame()
{
    MainScene* scene = new MainScene();

    scene->init();

    CCDirector::sharedDirector()->replaceScene( CCTransitionFlipX::create(0.8, scene) );
    scene->release();
}
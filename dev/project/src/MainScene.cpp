#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

bool MainScene::init()
{
    bool kRet = GameScene::init();

    CCSprite* pBackground = CCSprite::create();
    pBackground->initWithFile("data/testscenebg.png");
    pBackground->setPosition(VisibleRect::center());

    addChild(pBackground);

    return kRet;
}

void MainScene::onEnter()
{
    GameScene::onEnter();
}
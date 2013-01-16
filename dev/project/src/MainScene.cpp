#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenu.h"
#include "GameDelegate.h"

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

    IngameMenu* igmenu = new IngameMenu();
    igmenu->init();

    addChild(igmenu);

    igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));

    igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameScene::onEnter();
}

void MainScene::onMainMenuTap( CCObject* )
{
    GameDelegate::sharedGameDelegate()->returnToMainMenu();
}

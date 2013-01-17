#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{

}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();

    CCSprite* pBackground = CCSprite::create();
    pBackground->initWithFile("data/testscenebg.png");
    pBackground->setPosition(VisibleRect::center());

    addChild(pBackground);

    IngameMenuView* igmenu = new IngameMenuView();
    igmenu->init();

    addChild(igmenu);

    igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));

    igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();
}

void MainScene::onMainMenuTap( CCObject* )
{
    GameDelegate::sharedGameDelegate()->returnToMainMenu();
}

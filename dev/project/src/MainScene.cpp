#include "pch.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"
#include "Layer3D.h"

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
    pBackground->initWithFile("testscenebg.png");
    pBackground->setPosition(VisibleRect::center());

    IngameMenuView* igmenu = new IngameMenuView();
    igmenu->init();

    m_pBackground = Layer3D::create();

    addChild(pBackground); //temp
    addChild(m_pBackground);
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

#include "pch.h"
#include "MainMenuScene.h"
#include "VisibleRect.h"
#include "GameDelegate.h"

MainMenu::MainMenu()
{

}

bool MainMenu::init(bool fromGame)
{
    CCLayer::init();

    m_pMainMenu = CCMenu::create();

    CCString caption = "Start Game";
    if (fromGame)
        caption = "Resume Game";

    CCLabelTTF* label = CCLabelTTF::create(caption.getCString(), "Arial", 24);
    m_pStartButton = CCMenuItemLabel::create(label);
    m_pStartButton->setPosition( ccp( VisibleRect::center().x, VisibleRect::center().y) );

    //m_pMainMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (4 + 1) * 40));
    m_pMainMenu->setPosition(0.f, 0.f);
    m_pMainMenu->addChild(m_pStartButton);

    addChild(m_pMainMenu);

    setTouchEnabled(true);

    return true;
}

CCMenuItemLabel* MainMenu::getStartButton() const
{
    return m_pStartButton;
}

MainMenu::~MainMenu()
{
}

//------------------------------------------------------------------//
MainMenuScene::MainMenuScene(): m_pMainMenu(nullptr)
{

}

MainMenuScene::~MainMenuScene()
{

}

void MainMenuScene::onEnter()
{
    GameScene::onEnter();

}

bool MainMenuScene::init(bool fromGame)
{
    if (GameScene::init())
    {
        CCSprite* pBackground = CCSprite::create();
        pBackground->initWithFile("data/mmbg.png");
        pBackground->setPosition(VisibleRect::center());

        m_pMainMenu = new MainMenu();
        m_pMainMenu->init(fromGame);

        if (fromGame)
        {
            m_pMainMenu->getStartButton()->setTarget(this, menu_selector(MainMenuScene::returnCallback));
        }
        else
        {
            m_pMainMenu->getStartButton()->setTarget(this, menu_selector(MainMenuScene::startCallback));
        }

        addChild(pBackground);
        addChild(m_pMainMenu);
        m_pMainMenu->release();

        return true;
    }

    return false;
}

void MainMenuScene::startCallback(CCObject * pSender)
{
    GameDelegate::sharedGameDelegate()->startGame();
}


void MainMenuScene::returnCallback( CCObject * pSender )
{
    GameDelegate::sharedGameDelegate()->returnToGame();
}

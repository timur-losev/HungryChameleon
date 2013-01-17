#include "pch.h"
#include "MainMenuView.h"
#include "VisibleRect.h"

MainMenuView::MainMenuView()
{

}

bool MainMenuView::init(bool fromGame)
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

CCMenuItemLabel* MainMenuView::getStartButton() const
{
    return m_pStartButton;
}

MainMenuView::~MainMenuView()
{
}
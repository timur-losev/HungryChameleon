#include "Precompiled.h"
#include "IngameMenuView.h"
#include "VisibleRect.h"

IngameMenuView::IngameMenuView():
    m_pIngameMenu(nullptr),
    m_pBackToMainMenu(nullptr)
{

}

IngameMenuView::~IngameMenuView()
{

}

bool IngameMenuView::init()
{
    bool kRet = CCLayer::init();
    m_pIngameMenu = CCMenu::create();

    CCLabelTTF* label = CCLabelTTF::create("Main menu", "Arial", 24);
    m_pBackToMainMenu = CCMenuItemLabel::create(label);
    m_pBackToMainMenu->setPosition( ccp( VisibleRect::right().x - m_pBackToMainMenu->getContentSize().width / 2,
        VisibleRect::top().y - m_pBackToMainMenu->getContentSize().height / 2));

    m_pIngameMenu->setPosition(0, 0);
    m_pIngameMenu->addChild(m_pBackToMainMenu);

    addChild(m_pIngameMenu);

    setTouchEnabled(true);

    return kRet;
}

CCMenuItemLabel* IngameMenuView::getBackToMainMenu() const
{
    return m_pBackToMainMenu;
}

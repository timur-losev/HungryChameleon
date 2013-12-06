#include "Precompiled.h"
#include "MainMenuView.h"
#include "VisibleRect.h"
#include "TextManager.h"
#include "Resources.h"

MainMenuView::MainMenuView()
{

}

bool MainMenuView::init(bool fromGame)
{
    CCLayer::init();

	CCSprite* pBackground = CCSprite::create();
    pBackground->initWithFile("testscenebg.png");
    pBackground->setPosition(VisibleRect::center());
	addChild(pBackground);

	m_pMainMenu = CCMenu::create();

	CCLabelTTF* label = CCLabelTTF::create(TextManager::getString("STR_START_GAME").getCString(), Resources::FontShapleDots, Resources::FontSizeBig);
	//m_pStartButton = CCMenuItemLabel::create(label);
	//m_pStartButton->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y));

	//m_pMainMenu->setContentSize(CCSizeMake(VisibleRect::getVisibleRect().size.width, (4 + 1) * 40));
	m_pMainMenu->setPosition(0.f, 0.f);
	//m_pMainMenu->addChild(m_pStartButton);

#if 0
	addChild(m_pMainMenu);
#endif // 0

    setTouchEnabled(true);

	extension::UILayer* ul = extension::UILayer::create();
	extension::GUIReader reader;

	ul->addWidget(reader.widgetFromJsonFile("MainMenu/MainMenu.ExportJson"));
	m_pStartButton = ul->getWidgetByName("btn_start");
	addChild(ul);


    return true;
}

extension::UIWidget* MainMenuView::getStartButton() const
{
    return m_pStartButton;
}

MainMenuView::~MainMenuView()
{
}
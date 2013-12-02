#pragma once

class MainMenuView: public CCLayer
{
private:
    CCMenu*                 m_pMainMenu;
	extension::UIWidget*	m_pStartButton;
protected:
public:
    MainMenuView();
    ~MainMenuView();

    bool                    init(bool fromGame = false);

	extension::UIWidget*	getStartButton() const;
};
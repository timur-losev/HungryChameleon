#pragma once

class MainMenuView: public CCLayer
{
private:
    CCMenu*             m_pMainMenu;
    CCMenuItemLabel*    m_pStartButton;
protected:
public:
    MainMenuView();
    ~MainMenuView();

    bool             init(bool fromGame = false);

    CCMenuItemLabel* getStartButton() const;
};
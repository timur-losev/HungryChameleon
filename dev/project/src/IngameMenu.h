#pragma once

class IngameMenu: public CCLayer
{
private:
    CCMenu*                 m_pIngameMenu;
    CCMenuItemLabel*        m_pBackToMainMenu;
public:

    IngameMenu();
    ~IngameMenu();

    bool                    init();

    CCMenuItemLabel*        getBackToMainMenu() const;
};
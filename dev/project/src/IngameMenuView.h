#pragma once

class IngameMenuView: public CCLayer
{
private:
    CCMenu*                 m_pIngameMenu;
    CCMenuItemLabel*        m_pBackToMainMenu;
public:

    IngameMenuView();
    ~IngameMenuView();

    bool                    init();

    CCMenuItemLabel*        getBackToMainMenu() const;
};
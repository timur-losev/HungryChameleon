#pragma once

#include "GameScene.h"

class MainMenu: public CCLayer
{
private:
    CCMenu*             m_pMainMenu;
    CCMenuItemLabel*    m_pStartButton;
protected:
public:
    MainMenu();
    ~MainMenu();

    bool             init(bool fromGame = false);

    CCMenuItemLabel* getStartButton() const;
};

class MainMenuScene : public GameScene
{
private:
    MainMenu    *m_pMainMenu;
protected:
public:

    MainMenuScene();
    ~MainMenuScene();

    void startCallback(CCObject * pSender);
    void returnCallback(CCObject * pSender);

    virtual void onEnter();
    bool init(bool fromGame = false);
};
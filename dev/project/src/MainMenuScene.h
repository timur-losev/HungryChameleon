#pragma once

#include "GameSceneBase.h"

class MainMenuView;

class MainMenuScene : public GameSceneBase
{
private:
    MainMenuView    *m_pMainMenu;
protected:
public:

    MainMenuScene();
    ~MainMenuScene();

    void startCallback(CCObject * pSender);
    void returnCallback(CCObject * pSender);

    virtual void onEnter();
    bool init(bool fromGame = false);
};
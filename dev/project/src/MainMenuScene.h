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

	void                    startCallback(CCObject * pSender, extension::TouchEventType);
	void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);
};
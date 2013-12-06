#pragma once

#include "GameSceneBase.h"

class MainMenuScene : public GameSceneBase
{
	extension::UIWidget*	m_pStartButton;
public:
    MainMenuScene();
    ~MainMenuScene();

	void                    startCallback(CCObject * pSender, extension::TouchEventType);
	void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);
};
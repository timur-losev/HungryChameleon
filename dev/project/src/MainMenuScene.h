#pragma once

#include "GameSceneBase.h"

class MainMenuScene : public GameSceneBase
{
	extension::UIWidget*	m_pStartButton;

	void                    _startCallback(CCObject * pSender, extension::TouchEventType);
	void                    _optionsCallback(CCObject * pSender, extension::TouchEventType);

protected:

	void					_onUpdate(float dt);
public:
    MainMenuScene();
    ~MainMenuScene();

	void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);
};
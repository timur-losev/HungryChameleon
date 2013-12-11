#pragma once

#include "GameSceneBase.h"

class MainMenuScene : public GameSceneBase
{
public:
    MainMenuScene();
    ~MainMenuScene();

	void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);

private:
	void                    _startCallback(CCObject * pSender, extension::TouchEventType);
	void                    _optionsCallback(CCObject * pSender, extension::TouchEventType);
	void                    _shopCallback(CCObject * pSender, extension::TouchEventType);
	void					_onUpdate(float dt);
};
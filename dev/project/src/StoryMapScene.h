#pragma once

#include "GameSceneBase.h"

class StoryMapScene : public GameSceneBase
{
public:
	StoryMapScene();
	~StoryMapScene();
	
    bool                    init();

private:
	void                    _startSceneCallback(CCObject * pSender, extension::TouchEventType);
	void                    _optionsCallback(CCObject * pSender, extension::TouchEventType);
	void                    _shopCallback(CCObject * pSender, extension::TouchEventType);
	void					_onUpdate(float dt);
};
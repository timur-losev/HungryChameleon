#pragma once
#include "GameSceneBase.h"
#include "LeaderboardEntry.h"

class LeaderboardScene : public GameSceneBase
{
public:
    LeaderboardScene();
    ~LeaderboardScene();

    void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);

private:
    void                    _startCallback(CCObject * pSender, extension::TouchEventType);
    void                    _optionsCallback(CCObject * pSender, extension::TouchEventType);
    void                    _shopCallback(CCObject * pSender, extension::TouchEventType);
    void					_onUpdate(float dt);
    void					_initWithRecords(extension::UIScrollView*, extension::UIWidget*, const LeaderboardEntries_t&);

private:
};
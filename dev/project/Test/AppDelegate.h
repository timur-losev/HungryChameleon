#pragma once

#include <cocos2d.h>
using namespace cocos2d;

class GameController;

class AppDelegate: private cocos2d::CCApplication
{
private:
    GameController* m_pGameController;
protected:
public:
    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
};
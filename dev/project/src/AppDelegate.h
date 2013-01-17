#pragma once

class GameController;

class AppDelegate: private cocos2d::CCApplication
{
private:
    GameController*         m_pGameController;
protected:
public:
    virtual bool            applicationDidFinishLaunching();
    virtual void            applicationDidEnterBackground();
    virtual void            applicationWillEnterForeground();
};
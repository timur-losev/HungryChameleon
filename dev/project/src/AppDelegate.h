#pragma once

class AppDelegate: private cocos2d::CCApplication
{
private:
protected:
public:
    virtual bool            applicationDidFinishLaunching();
    virtual void            applicationDidEnterBackground();
    virtual void            applicationWillEnterForeground();
};
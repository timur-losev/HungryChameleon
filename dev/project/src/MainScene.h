#pragma once

#include "GameSceneBase.h"

class MainScene: public GameSceneBase
{
private:
protected:
public:
    MainScene();
    ~MainScene();

    bool         init();
    virtual void onEnter();

    void         onMainMenuTap(CCObject*);
};
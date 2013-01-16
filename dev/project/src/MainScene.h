#pragma once

#include "GameScene.h"

class MainScene: public GameScene
{
private:
protected:
public:
    MainScene();
    ~MainScene();

    bool         init();
    virtual void onEnter();
};
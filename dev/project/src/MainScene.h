#pragma once

#include "GameSceneBase.h"

class Layer3D;

class MainScene: public GameSceneBase
{
private:

    Layer3D*                m_pBackground;

protected:
public:
    MainScene();
    ~MainScene();

    bool                    init();
    virtual void            onEnter();

    void                    onMainMenuTap(CCObject*);
};
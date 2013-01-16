#pragma once
#include <cocos2d.h>
using namespace cocos2d;

class GameView;

class GameScene : public CCScene
{
private:
	GameView    *m_pGameView;
protected:
public:
    GameScene();
    virtual ~GameScene();

    virtual void onEnter();
    virtual void createInstance();
};
#pragma once

class GameSceneBase : public CCScene
{
private:
protected:
public:
    GameSceneBase();
    virtual ~GameSceneBase();

    virtual void onEnter();
};
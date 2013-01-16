#pragma once

class GameScene : public CCScene
{
private:
protected:
public:
    GameScene();
    virtual ~GameScene();

    virtual void onEnter();
    virtual void createInstance() = 0;
};
#pragma once

class GameDelegate
{
private:
    static GameDelegate*    s_SharedGameDelegate;
    void                    init();
public:

    GameDelegate();
    ~GameDelegate();

    void                    startGame();

    static GameDelegate*    sharedGameDelegate();
};
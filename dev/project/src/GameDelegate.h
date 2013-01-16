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
    void                    openMainMenu();
    void                    returnToMainMenu();
    void                    returnToGame();

    static GameDelegate*    sharedGameDelegate();
};
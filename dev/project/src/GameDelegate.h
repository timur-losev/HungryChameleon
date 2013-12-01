#pragma once

class SceneController;

class GameDelegate
{
public:

    GameDelegate();
    ~GameDelegate();

    void                    init();

    void                    startGame();
//    void                    openMainMenu();
//    void                    returnToMainMenu();
//    void                    returnToGame();

private:
	SceneController* m_sceneController = nullptr;
};

typedef Loki::SingletonHolder<GameDelegate, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedGameDelegate;
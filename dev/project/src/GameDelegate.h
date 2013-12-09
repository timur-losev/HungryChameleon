#pragma once

class SceneController;
class SaveController;
class Player;

class GameDelegate
{
public:

    GameDelegate();
    ~GameDelegate();

    void                    init();

    void                    startGame();

////////////////////////////////////////////////////////////
//// Save
	static SaveController*	getSaveController();
	void					saveNow();

////////////////////////////////////////////////////////////
//// Scene
	static SceneController* getSceneController();

////////////////////////////////////////////////////////////
//// Player
	static Player*			getPlayer();

private:
	SceneController*		m_sceneController = nullptr;
	SaveController*			m_saveController = nullptr;
	Player*					m_player = nullptr;
};

typedef Loki::SingletonHolder<GameDelegate, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedGameDelegate;

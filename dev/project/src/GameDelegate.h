#pragma once

class SceneController;
class SaveController;

class GameDelegate
{
public:

    GameDelegate();
    ~GameDelegate();

    void                    init();

    void                    startGame();

////////////////////////////////////////////////////////////
//// Save
	SaveController*			getSaveController();
	void					saveNow();

private:
	SceneController*		m_sceneController = nullptr;
	SaveController*			m_saveController = nullptr;
};

typedef Loki::SingletonHolder<GameDelegate, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedGameDelegate;
#pragma once

class SceneController;
class SaveController;
class Player;
class PopupController;
class LevelSettingsController;

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

	static PopupController* getPopupController();

	static LevelSettingsController* getLevelSettingsController();
private:
	SceneController*		m_sceneController = nullptr;
	SaveController*			m_saveController = nullptr;
	Player*					m_player = nullptr;
	PopupController*		m_popupController = nullptr;
	LevelSettingsController*m_levelSettingsController = nullptr;
};

typedef Loki::SingletonHolder<GameDelegate, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedGameDelegate;

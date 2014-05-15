#pragma once

class SceneController;
class SaveController;
class Player;
class PopupController;
class LevelSettingsController;
class OnlineController;

class GameDelegate
{
protected:
    SceneController*        m_sceneController = nullptr;
    SaveController*         m_saveController = nullptr;
    Player*                 m_player = nullptr;
    PopupController*        m_popupController = nullptr;
    LevelSettingsController*m_levelSettingsController = nullptr;
    OnlineController*       m_onlineController = nullptr;

public:

    GameDelegate();
    ~GameDelegate();

    void                    init();

    void                    startGame();

    ////////////////////////////////////////////////////////////
    //// Save
    SaveController*         getSaveController();
    void                    saveNow();

    ////////////////////////////////////////////////////////////
    //// Scene
    SceneController*        getSceneController();

    ////////////////////////////////////////////////////////////
    //// Player
    Player*                 getPlayer();

    PopupController*        getPopupController();

    LevelSettingsController* getLevelSettingsController();

    OnlineController*       getOnlineController();
};

typedef Loki::SingletonHolder<GameDelegate, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedGameDelegate;

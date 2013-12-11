#pragma once
#include "SceneModes.h"

class GameSceneBase;
class PopupBase;

class SceneController : public sigslot::has_slots<>
{
public:
	SceneController();
	~SceneController();

	void					launch();
	void					advanceToMode(ESceneModes);
	void					addPopup(PopupBase*);

	bool					canShowPopup();

private:
	GameSceneBase*			_createScene(ESceneModes);
	GameSceneBase*			_currentScene();
	void					_onPopupClosed();
	void					_onLanguageChanged(const std::string&);
};
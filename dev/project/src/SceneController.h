#pragma once
#include "SceneModes.h"

class GameSceneBase;

class SceneController : public sigslot::has_slots<>
{
public:
	SceneController();
	~SceneController();

	void Launch();
	void AdvanceToMode(ESceneModes);
	void EnterSubMode(ESceneSubmodes);
	void ExitSubmode();

private:
	GameSceneBase* m_sceneMode = nullptr;
	GameSceneBase* m_sceneSubmode = nullptr;

	GameSceneBase* _CreateScene(ESceneModes);
};
#pragma once

#include "SceneModes.h"

class SceneController;

class GameSceneBase : public CCScene
{
private:
	ESceneModes m_baseSceneMode;
	sigslot::signal1<ESceneModes> m_signalChangeScene;

protected:
	inline void				_AdvanceToScene(ESceneModes mode) { m_signalChangeScene(mode); }

public:
    GameSceneBase(ESceneModes);
    virtual ~GameSceneBase();

    virtual void            onEnter();
	inline ESceneModes		getMode() const { return m_baseSceneMode; }
	void                    AddSceneSlots(SceneController* scene);
};
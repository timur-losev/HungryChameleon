#pragma once

#include "SceneModes.h"

class SceneController;

class GameSceneBase : public CCScene
{
private:
	ESceneModes m_baseSceneMode;

protected:
	sigslot::signal1<ESceneModes> _AdvanceToScene;

public:
    GameSceneBase(ESceneModes);
    virtual ~GameSceneBase();

    virtual void            onEnter();
	inline ESceneModes		getMode() const { return m_baseSceneMode; }
	void                    AddSceneSlots(SceneController* scene);
};
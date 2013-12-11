#pragma once

#include "SceneModes.h"

class SceneController;

class GameSceneBase : public CCScene, public has_slots<>
{
private:
	ESceneModes				m_baseSceneMode;
	bool					m_baseIsPaused = false;

protected:
	sigslot::signal1<ESceneModes> _advanceToScene;

	virtual void			_onUpdate(float dt) = 0;

public:
    GameSceneBase(ESceneModes);
    virtual ~GameSceneBase();

    virtual void            onEnter();

	inline ESceneModes		getMode() const { return m_baseSceneMode; }
	void                    addSceneSlots(SceneController* scene);
	void					update(float dt);

	virtual bool			canShowPopup() const { return true; }

	void					setPaused(bool value);
	bool					isPaused() const;
};
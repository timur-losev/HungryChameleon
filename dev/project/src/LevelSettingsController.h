#pragma once
#include "SceneModes.h"

struct LevelSettings
{
	std::string levelName;
	std::string nextPosition;
	unsigned int time;
};

class LevelSettingsController : public sigslot::has_slots<>
{
	typedef std::map<std::string, LevelSettings> TevelSettingsMap_t;

public:
	LevelSettingsController();
	~LevelSettingsController();

	bool					init();
	const LevelSettings&	getSettingsForPoint(const std::string&);
	const std::string&		getStartingPoint();

private:
	TevelSettingsMap_t		m_levelMap;
	std::string				m_startingPoint;
};
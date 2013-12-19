#include "Precompiled.h"
#include "LevelSettingsController.h"

LevelSettingsController::LevelSettingsController()
{
	init();
}

LevelSettingsController::~LevelSettingsController()
{
}

bool LevelSettingsController::init()
{
	CCDictionary* lvlDict = CCDictionary::createWithContentsOfFile("levelsequence.plist");
	CCArray* points = lvlDict->allKeys();
	CCObject* point;
	CCARRAY_FOREACH(points, point)
	{
		std::string key = static_cast<CCString*>(point)->getCString();
		if (key == "start")
		{
			m_startingPoint = lvlDict->valueForKey(key)->getCString();
		}
		else
		{
			CCDictionary* settingsDict = static_cast<CCDictionary*>(lvlDict->objectForKey(key));
			assert(settingsDict);
			LevelSettings settings;
			settings.levelName = settingsDict->valueForKey("level")->getCString();
			settings.nextPosition = settingsDict->valueForKey("next")->getCString();
			settings.time = settingsDict->valueForKey("time")->intValue();
			m_levelMap[key] = settings;
		}
	}
	return true;
}

const LevelSettings& LevelSettingsController::getSettingsForPoint(const std::string& point)
{
	auto setting = m_levelMap.find(point);
	assert(setting != m_levelMap.end());
	return setting->second;
}

const std::string& LevelSettingsController::getStartingPoint()
{
	return m_startingPoint;
}
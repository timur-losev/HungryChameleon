#include "Precompiled.h"

#include "SaveController.h"

const char* SaveController::s_saveFile = "save.dat";
const float SaveController::s_autosaveInterval = 10; // seconds
const char* SaveController::s_saveVersion = "0.0.1";

namespace SaveKeys
{
	const char* Language	= "language";
	const char* Version		= "version";
};

SaveController::SaveController()
{
}

SaveController::~SaveController()
{
}

SaveController* SaveController::createController()
{
	SaveController* pRet = new SaveController();
	if (pRet != NULL)
	{
		pRet->autorelease();
	}
	return pRet;
}

void SaveController::save()
{
	m_saveData->writeToFile(s_saveFile);
}

bool SaveController::load()
{
	if (CCFileUtils::sharedFileUtils()->isFileExist(s_saveFile))
	{
		m_saveData = CCDictionary::createWithContentsOfFile(s_saveFile);
	}
	else
	{
		m_saveData = _createNewSave();
	}
	m_saveData->retain();
	
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&SaveController::_autosave), this, s_autosaveInterval, false);

	return true;
}

void SaveController::_autosave(float)
{
	save();
}

CCDictionary* SaveController::getDIct()
{
	return m_saveData;
}

CCDictionary* SaveController::_createNewSave()
{
	CCDictionary* dict = CCDictionary::create();
	CCString* version = CCString::create(s_saveVersion);
	dict->setObject(version, SaveKeys::Version);
	return dict;
}

std::string SaveController::getLanguage()
{
	if (m_saveData->objectForKey(SaveKeys::Language) == NULL)
		return std::string();

	return m_saveData->valueForKey(SaveKeys::Language)->m_sString;
}

void SaveController::setLanguage(const std::string& lang)
{
	CCString* str = CCString::create(lang);
	m_saveData->setObject(str, SaveKeys::Language);
}

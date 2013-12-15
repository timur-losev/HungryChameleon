#include "Precompiled.h"

#include "SaveController.h"
#include "EventController.h"
#include "TextManager.h"
#include "Player.h"
#include "GameDelegate.h"

const char* SaveController::s_saveFile = "save.dat";
const float SaveController::s_autosaveInterval = 300; // seconds
const char* SaveController::s_saveVersion = "0.0.1";

SaveController::SaveController()
{
	SharedEventController::Instance().changeLanguage.connect(this, &SaveController::setLanguage);
}

SaveController::~SaveController()
{
}

SaveController* SaveController::createController()
{
	SaveController* pRet = new SaveController();
	if (pRet)
	{
		pRet->autorelease();
	}
	return pRet;
}

void SaveController::save()
{
	//m_saveData->writeToFile(s_saveFile);
}

bool SaveController::load()
{
	if (CCFileUtils::sharedFileUtils()->isFileExist(s_saveFile))
	{
		//m_saveData = CCDictionary::createWithContentsOfFile(s_saveFile);
		m_saveData = _createNewSave();

	}
	else
	{
		m_saveData = _createNewSave();
		save();
	}
	m_saveData->retain();
	
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(SEL_SCHEDULE(&SaveController::_autosave), this, s_autosaveInterval, false);

	return true;
}

void SaveController::_autosave(float)
{
	GameDelegate::getPlayer()->dumpSave();
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
	CCString* lang = CCString::create(TextManager::s_English);
	dict->setObject(lang, SaveKeys::Language);
	CCInteger* highScore = CCInteger::create(0);
	dict->setObject(highScore, SaveKeys::HighScore);
	CCInteger* cash = CCInteger::create(1);
	dict->setObject(cash, SaveKeys::Cash);

	return dict;
}

std::string SaveController::getLanguage()
{
	if (m_saveData->objectForKey(SaveKeys::Language) == NULL)
		return std::string();

	return m_saveData->valueForKey(SaveKeys::Language)->getCString();
}

void SaveController::setLanguage(const std::string& lang)
{
	if (getLanguage() == lang && !lang.empty())
		return;

	CCString* str = CCString::create(lang);
	m_saveData->setObject(str, SaveKeys::Language);
	save();
}

int SaveController::getIntValue(const char* key)
{
	if (m_saveData->objectForKey(key) == NULL)
		return 0;
	return m_saveData->valueForKey(key)->intValue();
}

void SaveController::setIntValue(const char* key, int value)
{
	std::stringstream ss;
	ss << value;
	CCString* i = CCString::create(ss.str());
	m_saveData->setObject(i, key);
}

std::string SaveController::getStringValue(const char* key)
{
	return m_saveData->valueForKey(key)->getCString();
}

void SaveController::setStringValue(const char* key, const std::string& value)
{
	CCString* str = CCString::create(value);
	m_saveData->setObject(str, key);
}

CCDictionary* SaveController::getDictValue(const char* key)
{
	CCObject* dictObject = m_saveData->objectForKey(key);
	CCDictionary* dict = dynamic_cast<CCDictionary*>(dictObject);
	if (!dict)
	{
		dict = CCDictionary::create();
	}
	return dict;
}

void SaveController::setDictValue(const char* key, CCDictionary* value)
{
	m_saveData->setObject(value, key);
}

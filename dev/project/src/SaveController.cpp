#include "Precompiled.h"

#include "SaveController.h"
#include "EventController.h"
#include "TextManager.h"
#include "Player.h"
#include "GameDelegate.h"
#include "LocalStorage/LocalStorage.h"

//const float SaveController::s_autosaveInterval = 300; // seconds
const char* SaveController::s_saveVersion = "0.0.1";
const char* SaveController::s_saveFile = "save.dat";

SaveController::SaveController()
{
	SharedEventController::Instance().changeLanguage.connect(this, &SaveController::setLanguage);
    std::string file(s_saveFile);
#ifndef _WIN32
    NSString* docsDir;
    NSArray* dirPaths;
    dirPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    docsDir = dirPaths[0];
    NSString* databasePath = [[NSString alloc] initWithString:[docsDir stringByAppendingPathComponent:[NSString stringWithUTF8String:s_saveFile]]];
    file = [databasePath UTF8String];
#endif
	localStorageInit(file.c_str());
}

SaveController::~SaveController()
{
	localStorageFree();
}

/************************************************************/
/************************************************************/

void SaveController::_getValue(const char* key, int& out)
{
	out = 0;
	const char* value = localStorageGetItem(key);
	if (value)
	{
		out = atoi(value);
	}
}

void SaveController::_getValue(const char* key, std::string& out)
{
	out = "";
	const char* value = localStorageGetItem(key);
	if (value)
	{
		out = value;
	}
}

void SaveController::_getValue(const char* key, CCDictionary** out)
{
	const char* value = localStorageGetItem(key);
	if (value)
	{
		*out = CCFileUtils::sharedFileUtils()->createCCDictionaryWithData(value, strlen(value));
	}
	else
	{
		*out = CCDictionary::create();
	}
}

void SaveController::_setValue(const char* key, int value)
{
	std::stringstream ss;
	ss << value;
	localStorageSetItem(key, ss.str().c_str());
}

void SaveController::_setValue(const char* key, const std::string& value)
{
	localStorageSetItem(key, value.c_str());
}

void SaveController::_setValue(const char* key, CCDictionary* value)
{
	const char* plist = CCFileUtils::sharedFileUtils()->dumpCCDictionaryToData(value);
	if (plist)
	{
		localStorageSetItem(key, plist);
		delete[] plist;
	}
}

/************************************************************/
/************************************************************/

std::string SaveController::getVersion()
{
	std::string ret;
	_getValue(SaveKeys::Version, ret);
	return ret;
}

void SaveController::setVersion(const std::string& value)
{
	_setValue(SaveKeys::Version, value);
}

int SaveController::getHighScore()
{
	int ret = 0;
	_getValue(SaveKeys::HighScore, ret);
	return ret;
}

void SaveController::setHighScore(int value)
{
	_setValue(SaveKeys::HighScore, value);
}

int SaveController::getCash()
{
	int ret = 0;
	_getValue(SaveKeys::HighScore, ret);
	return ret;
}

void SaveController::setCash(int value)
{
	_setValue(SaveKeys::Cash, value);
}

std::string SaveController::getChipPosition()
{
	std::string ret;
	_getValue(SaveKeys::ChipPosition, ret);
	return ret;
}

void SaveController::setChipPosition(const std::string& value)
{
	_setValue(SaveKeys::ChipPosition, value);
}

CCDictionary* SaveController::getMapProgress()
{
	CCDictionary* ret;
	_getValue(SaveKeys::MapProgress, &ret);
	return ret;
}

void SaveController::setMapProgress(CCDictionary* value)
{
	_setValue(SaveKeys::MapProgress, value);
}

std::string SaveController::getLanguage()
{
	std::string ret;
	_getValue(SaveKeys::Language, ret);
	return ret;
}

void SaveController::setLanguage(const std::string& lang)
{
	_setValue(SaveKeys::Language, lang);
}

/************************************************************/
/************************************************************/

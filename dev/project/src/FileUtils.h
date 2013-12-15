#pragma once
#include "platform/CCFileUtils.h"

// Access files as blobs in database
class FileUtils : public cocos2d::CCFileUtils
{
protected:
	FileUtils();
	virtual bool init();
public:
	virtual ~FileUtils();
	
	static CCFileUtils* sharedFileUtils();

	virtual unsigned char* getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize);
	virtual std::string fullPathForFilename(const char* pszFileName);
	virtual std::string getWritablePath();
	virtual bool isFileExist(const std::string& strFilePath);	
};

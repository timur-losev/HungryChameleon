#include "Precompiled.h"
#include "FileUtils.h"
#include "VirtualFiles.h"

FileUtils::FileUtils()
{
	VirtualFiles::init();
}

FileUtils::~FileUtils()
{
	VirtualFiles::close();
}

bool FileUtils::init()
{
	return true;
}

CCFileUtils* FileUtils::sharedFileUtils()
{
	if (s_sharedFileUtils == NULL)
	{
		s_sharedFileUtils = new FileUtils();
	}
	return s_sharedFileUtils;
}

unsigned char* FileUtils::getFileData(const char* pszFileName, const char* pszMode, unsigned long * pSize)
{
	void* biffer; //aziriv-style
	VirtualFiles::getBlob(pszFileName, &biffer, pSize);
	return (unsigned char*)biffer;
}

std::string FileUtils::fullPathForFilename(const char* pszFileName)
{
	return pszFileName;
}

std::string FileUtils::getWritablePath()
{
	return std::string();
}

bool FileUtils::isFileExist(const std::string& strFilePath)
{
	return VirtualFiles::doesFileExists(strFilePath.c_str());
}

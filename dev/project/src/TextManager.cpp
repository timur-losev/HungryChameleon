#include "Precompiled.h"
#include "TextManager.h"
#include "Resources.h"

const std::string TextManager::s_English = "en";
const std::string TextManager::s_Russian = "ru";

TextManager::TextManager()
{
}


TextManager::~TextManager()
{
}

void TextManager::loadLanguage(const std::string& lang)
{
	if (m_currentLang == lang)
		return;

	if (m_stringsDict)
		m_stringsDict->release();

	m_currentLang = lang;
	std::string file = Resources::languageFile(m_currentLang);

	if (file.empty())
		{
		m_currentLang = lang;
		file = Resources::languageFile(m_currentLang);
	}

	m_stringsDict = CCDictionary::createWithContentsOfFile(file.c_str());
	m_stringsDict->retain();
}

const CCString TextManager::_getString(const std::string& key)
{	
#ifdef _DEBUG
	const CCString* str = m_stringsDict->valueForKey(key);
	if(str->length() == 0)
		return "NO_STRING_FOUND";
	return *str;
#else
	return *(m_stringsDict->valueForKey(key));
#endif
}

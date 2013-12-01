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
}

const std::string& TextManager::_getString(const std::string& key)
{
	CCObject* text = m_stringsDict->objectForKey(key);
	return "";
}

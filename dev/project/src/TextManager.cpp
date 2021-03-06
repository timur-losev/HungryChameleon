#include "Precompiled.h"
#include "TextManager.h"
#include "Resources.h"

#include "EventController.h"

extern std::string getLocalizationString(const std::string& key)
{
    return TextManager::getString(key).m_sString;
}

const std::string TextManager::s_English = "en";
const std::string TextManager::s_Russian = "ru";

TextManager::TextManager()
{
    SharedEventController::Instance().changeLanguage.connect(this, &TextManager::loadLanguage);
}

TextManager::~TextManager()
{
}

void TextManager::loadLanguage(const std::string& lang)
{
    if (m_currentLang == lang && !m_currentLang.empty())
        return;

    if (m_stringsDict)
        m_stringsDict->release();

    m_currentLang = lang;
    std::string file = Resources::languageFile(m_currentLang);

    if (file.empty())
    {
        m_currentLang = s_English;
        file = Resources::languageFile(m_currentLang);
    }

    m_stringsDict = CCDictionary::createWithContentsOfFile(file.c_str());
    m_stringsDict->retain();
}

CCString TextManager::_getString(const std::string& key)
{
#ifdef _DEBUG
    const CCString* str = m_stringsDict->valueForKey(key);
    if (str->length() == 0)
        return "no string";
    return *str;
#else
    return *(m_stringsDict->valueForKey(key));
#endif
}

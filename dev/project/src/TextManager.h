#pragma once

class TextManager;

typedef Loki::SingletonHolder<TextManager, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedTextManager;

class TextManager
{
public:
	TextManager();
	~TextManager();
	inline static const CCString	getString(const std::string& key) { return SharedTextManager::Instance()._getString(key); }

	void							loadLanguage(const std::string& lang);

public:
	static const std::string		s_English;
	static const std::string		s_Russian;

private:
	const CCString					_getString(const std::string& key);
	
private:
	CCDictionary*					m_stringsDict = nullptr;
	std::string						m_currentLang;
};

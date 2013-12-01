#pragma once

class TextManager
{
public:
	TextManager();
	~TextManager();
//	static const std::string&		getString(const std::string& key) { return Instance()._getString(key); }

	void							loadLanguage(const std::string& lang);

public:
	static const std::string		s_English;
	static const std::string		s_Russian;

private:
	const std::string&				_getString(const std::string& key);
	
private:
	CCDictionary*					m_stringsDict = nullptr;
	std::string						m_currentLang;
};

typedef Loki::SingletonHolder<TextManager, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedTextManager;
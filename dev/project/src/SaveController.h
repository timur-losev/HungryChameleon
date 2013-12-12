#pragma once

namespace SaveKeys
{
	static const char* Language = "language";
	static const char* Version = "version";
	static const char* HighScore = "high_score";
	static const char* Cash = "cash";
	static const char* TokenPosition = "token_map_position";
	static const char* MapProgress = "map_progress";
};

class SaveController : public CCObject, public has_slots<>
{
	static const char* s_saveFile;
	static const float s_autosaveInterval;
	static const char* s_saveVersion;

public:
	SaveController();
	virtual ~SaveController();

	static SaveController*	createController();
    bool					load();
    void					save();

	std::string				getLanguage();
	void					setLanguage(const std::string&);

	int						getIntValue(const char* key);
	void					setIntValue(const char* key, int value);

	std::string				getStringValue(const char* key);
	void					setStringValue(const char* key, const std::string& value);

	CCDictionary*			getDictValue(const char* key);
	void					setDictValue(const char* key, CCDictionary* value);

	CCDictionary*			getDIct();

private:
	void					_autosave(float);
	CCDictionary*			_createNewSave();

private:
	CCDictionary*			m_saveData = nullptr;
};
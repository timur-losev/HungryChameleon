#pragma once

namespace SaveKeys
{
	static const char* Language = "language";
	static const char* Version = "version";
	static const char* HighScore = "high_score";
	static const char* Cash = "cash";
	static const char* ChipPosition = "chip_map_position";
	static const char* MapProgress = "map_progress";

	static const char* FacebookToken = "facebook_token";
};

class SaveController : public CCObject, public has_slots<>
{
	static const char* s_saveFile;
	static const char* s_saveVersion;

public:
	SaveController();
	virtual ~SaveController();

// Savable variables interface
	std::string				getLanguage();
	void					setLanguage(const std::string&);

	std::string				getVersion();
	void					setVersion(const std::string&);

	int						getHighScore();
	void					setHighScore(int);

	int						getCash();
	void					setCash(int);

	std::string				getChipPosition();
	void					setChipPosition(const std::string&);

	CCDictionary*			getMapProgress();
	void					setMapProgress(CCDictionary*);

private:
	void					_getValue(const char* key, int& out);
	void					_getValue(const char* key, std::string& out);
	void					_getValue(const char* key, CCDictionary**);

	void					_setValue(const char* key, int);
	void					_setValue(const char* key, const std::string&);
	void					_setValue(const char* key, CCDictionary*);
};
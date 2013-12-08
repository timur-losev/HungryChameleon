#pragma once

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

	CCDictionary*			getDIct();

private:
	void					_autosave(float);
	CCDictionary*			_createNewSave();

private:
	CCDictionary*			m_saveData = nullptr;
};
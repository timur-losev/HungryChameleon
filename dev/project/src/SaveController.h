#pragma once

class SaveController : public CCDictionary
{
	static const char* s_saveFile;

	const unsigned int m_autosaveInterval = 300; // seconds
public:
	SaveController();
	virtual ~SaveController();

	static SaveController*	createController();
    bool					load();
    void					save();

	inline const unsigned int getAutosaveInterval() const { return m_autosaveInterval; }
private:
	CCDictionary* m_saveData;
};
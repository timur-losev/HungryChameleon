#pragma once

class SaveController
{
public:
	SaveController();
	~SaveController();

    bool					load();
    void					save();

private:
	CCDictionary* m_saveData;
};
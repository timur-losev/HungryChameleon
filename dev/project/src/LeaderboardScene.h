#pragma once

#include "GameSceneBase.h"

struct LeaderboardEntry
{
	LeaderboardEntry(const std::string _name, int _score, int _rank)
					:name(_name), score(_score), rank(_rank){}

	std::string name;
	int score;
	int rank;
};

class LeaderboardScene : public GameSceneBase
{
	typedef std::vector<LeaderboardEntry> Entries_t;

public:
	LeaderboardScene();
	~LeaderboardScene();

	void                    returnCallback(CCObject * pSender, extension::TouchEventType);

    virtual void            onEnter();
    bool                    init(bool fromGame = false);

private:
	void                    _startCallback(CCObject * pSender, extension::TouchEventType);
	void                    _optionsCallback(CCObject * pSender, extension::TouchEventType);
	void                    _shopCallback(CCObject * pSender, extension::TouchEventType);
	void					_onUpdate(float dt);
	void					_initWithRecords(extension::UIScrollView*, extension::UIWidget*, const Entries_t&);

private:
};
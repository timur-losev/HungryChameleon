#pragma once
#include "LeaderboardEntry.h"

class OnlineController : public CCObject
{
public:

	OnlineController();
	~OnlineController();

    const LeaderboardEntries_t& getEntries();

	void						_discoverServer(float = 0);
	void						_onServerDiscovered(extension::CCHttpClient* client, extension::CCHttpResponse* response);

	void						_loadLeaderboard(float = 0);
	void						_onLeaderboardLoaded(extension::CCHttpClient* client, extension::CCHttpResponse* response);
private:
	LeaderboardEntries_t		m_leaderboardEntries;
	std::string					m_server;


	static const float s_discoveryRetryInterval;
	static const float s_leaderboardRetryInterval;
	static const float s_leaderboardRefreshInterval;

};


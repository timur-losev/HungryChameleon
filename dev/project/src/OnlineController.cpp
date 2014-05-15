#include "Precompiled.h"
#include "OnlineController.h"
#include "LeaderboardScene.h"
#include "EventController.h"

using namespace extension;

const float OnlineController::s_discoveryRetryInterval = 3; // retry discovery if failed
const float OnlineController::s_leaderboardRetryInterval = 3; // retry leaderboard if failed
const float OnlineController::s_leaderboardRefreshInterval = 300; // refresh leaderboard


OnlineController::OnlineController()
{
	_discoverServer();
}

OnlineController::~OnlineController()
{
}

void OnlineController::_discoverServer(float)
{
	CCLog("== discovering server");
	CCHttpRequest* request = new CCHttpRequest;
	request->setUrl("https://dl.dropboxusercontent.com/u/19446960/discover/discover.html");
	request->setRequestData("", 1);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, httpresponse_selector(OnlineController::_onServerDiscovered));
	CCHttpClient::getInstance()->send(request);
}

void OnlineController::_onServerDiscovered(extension::CCHttpClient* client, extension::CCHttpResponse* response)
{
	if (response->isSucceed())
	{
		CCLog("== discover server succseeded");
		std::vector<char>* data = response->getResponseData();
		const char* begin = &(*data)[0];
		const char* end = begin + data->size();
		m_server = std::string(begin, end);
		_loadLeaderboard();
	}
	else
	{
		CCLog("== discover server failed. Error: %s", response->getErrorBuffer());
		CCDirector::sharedDirector()->getScheduler()->
			scheduleSelector(SEL_SCHEDULE(&OnlineController::_discoverServer), this, s_discoveryRetryInterval, 0, 0, false);
	}
}

void OnlineController::_loadLeaderboard(float)
{
	CCLog("== loading leaderboard");
	CCHttpRequest* request = new CCHttpRequest;
	std::string adr = m_server + "/get";
	request->setUrl(adr.c_str());
	request->setRequestData("", 1);
	request->setRequestType(CCHttpRequest::kHttpGet);
	request->setResponseCallback(this, httpresponse_selector(OnlineController::_onLeaderboardLoaded));
	CCHttpClient::getInstance()->send(request);
}

void OnlineController::_onLeaderboardLoaded(CCHttpClient* client, CCHttpResponse* response)
{
	if (response->isSucceed())
	{
		CCLog("== leaderboard loading succseeded");
		m_leaderboardEntries.clear();

		CSJson::Reader reader;
		std::vector<char>* data = response->getResponseData();
		CSJson::Value value;
		const char* begin = &(*data)[0];
		const char* end = begin + data->size();
		reader.parse(begin, end, value, false);
		if (value.isArray())
		{
			for (CSJson::ArrayIndex i = 0; i < value.size(); ++i)
			{
				const CSJson::Value jsonEntry = value[i];
				LeaderboardEntry entry;
				entry.name = jsonEntry.get("display_name", "").asCString();
				entry.score = atoi(jsonEntry.get("score", "0").asCString());
				entry.rank = atoi(jsonEntry.get("rank", "0").asCString());
				m_leaderboardEntries.push_back(entry);
			}
		}
		SharedEventController::Instance().onLeaderboardLoaded();
		// schedule refresh
		CCDirector::sharedDirector()->getScheduler()->
			scheduleSelector(SEL_SCHEDULE(&OnlineController::_loadLeaderboard), this, s_leaderboardRefreshInterval, 0, 0, false);
	}
	else
	{
		CCLog("== leaderboard loading failed. Error: %s", response->getErrorBuffer());
		// schedule retry
		CCDirector::sharedDirector()->getScheduler()->
			scheduleSelector(SEL_SCHEDULE(&OnlineController::_loadLeaderboard), this, s_leaderboardRetryInterval, 0, 0, false);
	}
}

const LeaderboardEntries_t& OnlineController::getEntries()
{
	return m_leaderboardEntries;
}

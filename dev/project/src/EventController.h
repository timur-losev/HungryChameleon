#pragma once

class EventController : public sigslot::has_slots<>
{
public:
	EventController();
	virtual ~EventController();

	signal1<const std::string&>		changeLanguage;

	signal1<int>					gameFinishedWithScore;
	signal2<int, int>				playerHighScoreChanged;	// old score, new score
	signal2<int, int>				playerCashChanged;		// old value, new value
	signal2<int, int>				playerScoreChanged;		// old score, new score

	signal0<>						popupClosed;

	signal1<const std::string&>		gameStartedWithLevel;	// level name

	signal0<>						onLeaderboardLoaded;
};

typedef Loki::SingletonHolder<EventController, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedEventController;

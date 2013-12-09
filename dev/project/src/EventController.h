#pragma once

class EventController : public sigslot::has_slots<>
{
public:
	EventController();
	virtual ~EventController();

	signal1<const std::string&>		changeLanguage;

	signal1<int>					gameFinishedWithScore;
	signal1<int>					playerHighScoreChanged;
	signal1<int>					playerCashChanged;
	signal1<int>					playerScoreChanged;
};

typedef Loki::SingletonHolder<EventController, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedEventController;

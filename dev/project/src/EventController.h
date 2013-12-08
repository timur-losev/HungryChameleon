#pragma once

#include "sigslot.h"

class EventController : public sigslot::has_slots<>
{
public:
	EventController();
	~EventController();

	sigslot::signal1<const std::string&> ChangeLanguage;

};

typedef Loki::SingletonHolder<EventController, Loki::CreateUsingNew, Loki::DefaultLifetime> SharedEventController;

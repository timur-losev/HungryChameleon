#include "Precompiled.h"
#include "Resources.h"
#include "TextManager.h"

const char* Resources::FontShapleDots		= "data/brookeshappelldots.ttf";

const float Resources::FontSizeSmall		= 10.0f;
const float Resources::FontSizeMedium		= 50.0f;
const float Resources::FontSizeBig			= 68.0f;

const std::string Resources::languageFile(const std::string& lang)
{
	if (lang == TextManager::s_English)
	{
		return "en.plist";
	}
	else if (lang == TextManager::s_Russian)
	{
		return "ru.plist";
	}
	else
	{
		return "";
	}
}

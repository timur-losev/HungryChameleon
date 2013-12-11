#include "Precompiled.h"
#include "PopupLanguage.h"

#include "GameDelegate.h"
#include "EventController.h"
#include "TextManager.h"

PopupLanguage::PopupLanguage()
{
	init();
}

PopupLanguage::~PopupLanguage()
{

}

bool PopupLanguage::init()
{
	bool ret = CCScene::init();

	extension::UILayer* ul = extension::UILayer::create();
	extension::GUIReader reader;
	ul->addWidget(reader.widgetFromJsonFile("MainMenu/LangSelect.ExportJson"));
	addChild(ul);

	extension::UIWidget* button;

	button = ul->getWidgetByName("popup_button_cancel");
	if (button)
	{
		button->addTouchEventListener(this, toucheventselector(PopupLanguage::_onCancel));
	}

	button = ul->getWidgetByName("button_en");
	if (button)
	{
		button->addTouchEventListener(this, toucheventselector(PopupLanguage::_onLangEn));
	}
	button = ul->getWidgetByName("button_ru");
	if (button)
	{
		button->addTouchEventListener(this, toucheventselector(PopupLanguage::_onLangRu));
	}

	return ret;
}

void PopupLanguage::_onLangEn(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		SharedEventController::Instance().changeLanguage(TextManager::s_English);
		_closePopup();
	}
}

void PopupLanguage::_onLangRu(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		SharedEventController::Instance().changeLanguage(TextManager::s_Russian);
		_closePopup();
	}
}

void PopupLanguage::_onCancel(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
	{
		_closePopup();
	}
}

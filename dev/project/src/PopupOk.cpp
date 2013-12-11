#include "Precompiled.h"
#include "PopupOk.h"

PopupOk::PopupOk()
{

}

PopupOk::PopupOk(const std::string& str)
{
	init(str);
}

PopupOk::~PopupOk()
{

}

bool PopupOk::init(const std::string& text)
{
	bool ret = CCScene::init();

	extension::UILayer* ul = extension::UILayer::create();
	extension::GUIReader reader;
	ul->addWidget(reader.widgetFromJsonFile("MainMenu/PopupOk.ExportJson"));
	addChild(ul);

	extension::UIWidget* buttonOk = ul->getWidgetByName("popup_button_ok");
	if (buttonOk)
	{
		buttonOk->addTouchEventListener(this, toucheventselector(PopupOk::_onOkButtonPressed));
	}
	
	extension::UILabel* textField = dynamic_cast<extension::UILabel*>(ul->getWidgetByName("popup_text"));
	if (textField)
	{
		textField->setText(text.c_str());
	}

	return ret;
}

void PopupOk::_onOkButtonPressed(CCObject * pSender, extension::TouchEventType ev)
{
	if (ev == extension::TOUCH_EVENT_ENDED)
		_closePopup();
}

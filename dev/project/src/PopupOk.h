#pragma once

#include "PopupBase.h"

class PopupOk : public PopupBase
{
public:
	PopupOk();
	~PopupOk();

	bool			init(const std::string& text);

protected:
	void			_onOkButtonPressed(CCObject * pSender, extension::TouchEventType ev);

};
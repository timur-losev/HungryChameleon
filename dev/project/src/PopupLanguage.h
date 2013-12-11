#pragma once

#include "PopupBase.h"

class PopupLanguage : public PopupBase
{
public:
	PopupLanguage();
	~PopupLanguage();

	bool					init();

private:

	void					_onLangEn(CCObject * pSender, extension::TouchEventType ev);
	void					_onLangRu(CCObject * pSender, extension::TouchEventType ev);
	void					_onCancel(CCObject * pSender, extension::TouchEventType ev);
};

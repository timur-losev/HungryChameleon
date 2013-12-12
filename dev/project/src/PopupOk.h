#pragma once

#include "PopupBase.h"
#ifndef _WIN32
#include <FacebookSDK.h>

#import "AppDelegateIos.h"
#endif


class PopupOk : public PopupBase
#ifndef _WIN32
//, public FBLoginViewDelegate
#endif

{
public:
	PopupOk();
	~PopupOk();
	PopupOk(const std::string&);

	bool			init(const std::string& text);

protected:
	void			_onOkButtonPressed(CCObject * pSender, extension::TouchEventType ev);
    
    void            facebook();

};
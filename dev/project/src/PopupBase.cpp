#include "Precompiled.h"
#include "PopupBase.h"

#include "EventController.h"

PopupBase::PopupBase()
{

}

PopupBase::~PopupBase()
{

}

void PopupBase::_closePopup()
{
	if (getParent())
	{
		getParent()->removeChild(this);
		SharedEventController::Instance().popupClosed();
	}
}

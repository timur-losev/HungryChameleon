#pragma once

class PopupBase : public CCScene, public has_slots<>
{
public:
	PopupBase();
	virtual ~PopupBase();

protected:
	void			_closePopup();

};

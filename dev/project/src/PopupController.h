#pragma once

class PopupBase;

class PopupController : public has_slots<>, public CCObject
{
public:
	PopupController();
	~PopupController();

	static PopupController*	createController();

	void					shedulePopup(PopupBase* popup, float delay);
	void					queuePopup(PopupBase*);

	void					update(float dt);

private:
	void					_onPopupClosed();
	bool					_canShowPopup();
	void					_showPopup(PopupBase* popup);

private:
	std::list<PopupBase*>	m_queue;
	bool					m_isShowingPopup = false;

};
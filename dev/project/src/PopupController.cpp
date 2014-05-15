#include "Precompiled.h"
#include "PopupController.h"

#include "PopupBase.h"
#include "EventController.h"
#include "GameDelegate.h"
#include "SceneController.h"

PopupController::PopupController()
{
    SharedEventController::Instance().popupClosed.connect(this, &PopupController::_onPopupClosed);
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
}

PopupController::~PopupController()
{

}

void PopupController::shedulePopup(PopupBase* popup, float delay)
{
    assert(false && "todo!");
}

void PopupController::queuePopup(PopupBase* popup)
{
    m_queue.push_back(popup);
}

void PopupController::update(float dt)
{
    if ((m_queue.size() > 0) && _canShowPopup())
    {
        _showPopup(m_queue.front());
        m_queue.pop_front();
    }
}

void PopupController::_onPopupClosed()
{
    m_isShowingPopup = false;
}

bool PopupController::_canShowPopup()
{
    // some scenes can prevent popup to show so we need to ask current scene
    return !m_isShowingPopup && SharedGameDelegate::Instance().getSceneController()->canShowPopup();
}

void PopupController::_showPopup(PopupBase* popup)
{
    SharedGameDelegate::Instance().getSceneController()->addPopup(popup);
}

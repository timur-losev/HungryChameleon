#include "Precompiled.h"
#include "MatrixStateIdle.h"
#include "MatrixController.h"

MatrixStateIdle::MatrixStateIdle(MatrixController* ctrl):
IMatrixState(ctrl),
m_waitForThisTouch(nullptr)
{
    ctrl->m_onTouchBegan.connect(this, &MatrixStateIdle::onTouchBeganSignal);
}

MatrixStateIdle::~MatrixStateIdle()
{

}

void MatrixStateIdle::update(float dt)
{

}

IMatrixState::Status::Enum MatrixStateIdle::getStatus() const
{
    return m_waitForThisTouch != nullptr ? IMatrixState::Status::Finished : IMatrixState::Status::Working;
}

void MatrixStateIdle::onTouchBeganSignal(CCTouch* t, CCEvent*)
{
    m_waitForThisTouch = t;
}

void MatrixStateIdle::reset()
{
    m_waitForThisTouch = nullptr;
}

CCTouch* MatrixStateIdle::getTouch() const
{
    return m_waitForThisTouch;
}

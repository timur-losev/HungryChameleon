#pragma once

#include "IMatrixState.h"

class MatrixStateIdle : public IMatrixState, public has_slots<>
{
private:
    CCTouch*       m_waitForThisTouch;

private:

    void onTouchBeganSignal(CCTouch*, CCEvent*);

public:
    MatrixStateIdle(MatrixController*);

    virtual ~MatrixStateIdle();

    virtual void update(float dt) override;
    virtual IMatrixState::Status::Enum getStatus() const override;
    virtual void stateEnter() override;
    virtual void stateLeave() override;

    CCTouch*     getTouch() const;
};
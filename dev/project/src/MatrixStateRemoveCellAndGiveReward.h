#pragma once

#include "IMatrixState.h"

class MatrixStateRemoveCellAndGiveReward : public IMatrixState
{
private:
public:
    MatrixStateRemoveCellAndGiveReward(MatrixController*);
    virtual ~MatrixStateRemoveCellAndGiveReward();

    virtual void        update(float dt) override;
    virtual IMatrixState::Status::Enum     getStatus() const override;
    virtual void        stateEnter() override;
    virtual void        stateLeave() override;
};
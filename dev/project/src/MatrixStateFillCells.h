#pragma once

#include "IMatrixState.h"

class MatrixStateFillCells : public IMatrixState
{
private:
    IMatrixState::Status::Enum m_status;
public:

    MatrixStateFillCells(MatrixController*);
    virtual ~MatrixStateFillCells();

    virtual void        update(float dt) override;
    virtual IMatrixState::Status::Enum     getStatus() const override;
    virtual void        stateEnter() override;
    virtual void        stateLeave() override;
};
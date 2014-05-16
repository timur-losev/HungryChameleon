#pragma once

#include "IMatrixState.h"

class MatrixStateBlink : public IMatrixState
{
public:
    MatrixStateBlink(MatrixController*);
    virtual ~MatrixStateBlink();

    virtual void update(float dt) override;
    virtual IMatrixState::Status::Enum getStatus() const override;
    virtual void reset() override;
};
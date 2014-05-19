#pragma once

#include "MatrixSateType.h"

class MatrixController;

class IMatrixState
{
public:

    class Status
    {
    public:
        enum Enum
        {
            Working,
            Finished,
            Failed,
            Other
        };
    };

    IMatrixState *next = nullptr, *prev = nullptr, *other = nullptr;

protected:
    MatrixController* m_matrixController;
    MatrixSateType::Enum    m_stateType;
public:
    IMatrixState(MatrixController*, MatrixSateType::Enum stateType);
    virtual ~IMatrixState() {};

    virtual void update(float dt) = 0;
    virtual Status::Enum getStatus() const = 0;

    virtual void stateEnter() = 0;
    virtual void stateLeave() = 0;

    MatrixSateType::Enum getStateType() const;

    virtual void init(MatrixController*) {};
};

#pragma once

class MatrixController;

//@TODO: Timur: stateEnter, stateLeave should be here. ASAP

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

protected:
    MatrixController* m_matrixController;
public:
    IMatrixState(MatrixController*);
    virtual ~IMatrixState() {};

    virtual void update(float dt) = 0;
    virtual Status::Enum getStatus() const = 0;

    virtual void reset() = 0; //! for reusing a state

    virtual void init(MatrixController*) {};
};

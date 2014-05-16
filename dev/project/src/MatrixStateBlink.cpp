#include "Precompiled.h"
#include "MatrixStateBlink.h"

MatrixStateBlink::MatrixStateBlink(MatrixController* ctrl) : IMatrixState(ctrl)
{

}

MatrixStateBlink::~MatrixStateBlink()
{

}

void MatrixStateBlink::update(float dt)
{

}

IMatrixState::Status::Enum MatrixStateBlink::getStatus() const
{
    return IMatrixState::Status::Finished;
}

void MatrixStateBlink::reset()
{

}

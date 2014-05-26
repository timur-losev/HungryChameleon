#include "Precompiled.h"
#include "IMatrixState.h"
#include "CellField.h"

IMatrixState::IMatrixState(MatrixController* ctrl, MatrixStateType::Enum stateType):
m_matrixController(ctrl), m_stateType(stateType)
{
}

MatrixStateType::Enum IMatrixState::getStateType() const
{
    return m_stateType;
}

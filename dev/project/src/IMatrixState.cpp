#include "Precompiled.h"
#include "IMatrixState.h"
#include "CellField.h"

IMatrixState::IMatrixState(MatrixController* ctrl, MatrixSateType::Enum stateType):
m_matrixController(ctrl), m_stateType(stateType)
{
}

MatrixSateType::Enum IMatrixState::getStateType() const
{
    return m_stateType;
}

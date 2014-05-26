#include "Precompiled.h"
#include "MatrixStateFillCells.h"

#include "MatrixController.h"

#include "CellContainer.h"

MatrixStateFillCells::MatrixStateFillCells(MatrixController* ctr):
IMatrixState(ctr, MatrixStateType::FillCells),
m_status(IMatrixState::Status::Working)
{

}

MatrixStateFillCells::~MatrixStateFillCells()
{

}

void MatrixStateFillCells::update(float dt)
{

}

IMatrixState::Status::Enum MatrixStateFillCells::getStatus() const
{
    return m_status;
}

void MatrixStateFillCells::stateEnter()
{
    MatrixController::Matrix_t& mat = m_matrixController->getMatrix();

    for (size_t x = 0; x < m_matrixController->totalWidth(); ++x)
    {
        for (size_t y = 0; y < m_matrixController->totalHeight(); ++y)
        {
            if (mat[x][y]->isValid() == false)
            {
                mat[x][y]->generateRandomCell(m_matrixController->getCellSize());
            }
        }
    }

    m_status = IMatrixState::Status::Finished;
}

void MatrixStateFillCells::stateLeave()
{

}

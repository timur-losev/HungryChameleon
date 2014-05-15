#include "Precompiled.h"
#include "MatrixStateFill.h"
#include "MatrixController.h"
#include "CellContainer.h"
#include "Cell.h"
#include "MatrixStateMatching.h"

MatrixStateFill::MatrixStateFill()
{

}

MatrixStateFill::~MatrixStateFill()
{

}

void MatrixStateFill::init(MatrixController* controller)
{
    m_controller = controller;
}

void MatrixStateFill::update(float dt)
{
    _execute();
}

bool MatrixStateFill::isFinished()
{
	return m_isFinished;
}

void MatrixStateFill::_execute()
{
    std::list<std::list<CellContainer*> > matchings;
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();

    // Sweep visible rectangle
    int iMin = 0;
    int iMax = iMin + m_controller->totalWidth();
    int jMin = 0;
    int jMax = jMin + m_controller->totalHeight();
    for (uint32_t i = iMin; i < iMax; ++i)
    {
        for (uint32_t j = jMin; j < jMax; ++j)
        {
            if (matrix[i][j])
            {
                if (**matrix[i][j])
                {
                    matrix[i][j]->clean();
                }
                else
                {
                    _dropDown(matrix[i][j]);
                }
                (*matrix[i][j])->travelsed = false;
            }
        }
    }
    m_controller->pushState(new MatrixStateMatching);
    m_isFinished = true;
}

void MatrixStateFill::_dropDown(CellContainer* cellToMove)
{
    int closest = 0;
    CellContainer* cell = cellToMove->up();
    while (cell)
    {
        if (**cell)
        {
            break;
        }
        else
        {
            ++closest;
        }
        cell = cell->up();
    }
    
    cell = cellToMove;
    bool isCenterQuad = (cell->colId > m_controller->additionalWidth())
                        && 
                        (cell->colId < m_controller->additionalWidth() + m_controller->visibleWidth());

    int maxIndex = isCenterQuad ? (m_controller->totalHeight() - 1) : (m_controller->additionalHeight() + m_controller->visibleHeight() - 1);

    if (closest + cellToMove->rowId == maxIndex)
    {
        // Nothing to drop down
        while (cell)
        {
            cell->generateRandomCell(ccp(m_controller->getCellWidth(), m_controller->getCellHeight()));
            cell = cell->up();
        }
        return;
    }
    else
    {
        // Drop down one by one
        int row = cell->rowId + closest + 1;
        cellToMove->attachCell(m_controller->getMatrix()[cellToMove->colId][row]->pass());
    }
}

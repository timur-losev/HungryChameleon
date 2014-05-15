#include "Precompiled.h"
#include "MatrixStateMatching.h"
#include "MatrixController.h"

#include "CellContainer.h"
#include "Cell.h"
#include "MatrixStateRemove.h"

#include "MatrixStateIdle.h"

MatrixStateMatching::MatrixStateMatching(MatrixController* ctr) :
IMatrixState(ctr),
m_isFinished(false)
{

}

MatrixStateMatching::~MatrixStateMatching()
{

}

void MatrixStateMatching::update(float dt)
{
    // get previous state for retrieving the hit result from it
    const MatrixStateIdle* stateIdle = static_cast<const MatrixStateIdle*>(m_matrixController->getState(MatrixSateType::Idle));
    CCTouch* touch = stateIdle->getTouch();

    if (touch)
    {
        CellContainer* hitCell = m_matrixController->getCellAtTouchPoint(touch->getLocation());

        if (hitCell)
        {
            _floodFill(hitCell, hitCell->getColour(), m_matchedCells);

            if (m_matchedCells.size() >= 3)
            {

            }
            else
            {
                m_matchedCells.clear();
            }
        }
    }
}

IMatrixState::Status::Enum MatrixStateMatching::getStatus() const
{
    return IMatrixState::Status::Working;
}

void MatrixStateMatching::_floodFill(CellContainer* cellCnt, Cell::Colour targetColour, MatchedCells_t& matchingList)
{
    if (cellCnt && (cellCnt->isTravelsed() || cellCnt->getColour() != targetColour))
    {
        return;
    }

    cellCnt->setTravelsed(true);
    cellCnt->clean();

    matchingList.push_back(cellCnt);

    if (cellCnt->right() && cellCnt->right()->isVisible())
    {
        _floodFill(cellCnt->right(), targetColour, matchingList);
    }
    if (cellCnt->left() && cellCnt->left()->isVisible())
    {
        _floodFill(cellCnt->left(), targetColour, matchingList);
    }
    if (cellCnt->up() && cellCnt->up()->isVisible())
    {
        _floodFill(cellCnt->up(), targetColour, matchingList);
    }
    if (cellCnt->down() && cellCnt->down()->isVisible())
    {
        _floodFill(cellCnt->down(), targetColour, matchingList);
    }
}

void MatrixStateMatching::reset()
{
    m_matchedCells.clear();
}

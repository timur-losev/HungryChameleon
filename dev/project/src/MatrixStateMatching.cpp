#include "Precompiled.h"
#include "MatrixStateMatching.h"
#include "MatrixController.h"

#include "CellContainer.h"
#include "Cell.h"

#include "MatrixStateIdle.h"

MatrixStateMatching::MatrixStateMatching(MatrixController* ctr) :
IMatrixState(ctr, MatrixStateType::SearchForMatches),
m_status(IMatrixState::Status::Working)
{

}

MatrixStateMatching::~MatrixStateMatching()
{

}

void MatrixStateMatching::update(float dt)
{

}

IMatrixState::Status::Enum MatrixStateMatching::getStatus() const
{
    return m_status;
}

bool MatrixStateMatching::_isCellTravelsed(CellContainer* cell)
{
    MatchedCells_t::const_iterator it = std::find(m_travelsedCells.begin(), m_travelsedCells.end(), cell);

    return it != m_travelsedCells.end();
}

void MatrixStateMatching::_floodFill(CellContainer* cellCnt, Cell::Colour targetColour, MatchedCells_t& matchingList)
{
    if (cellCnt && (cellCnt->getColour() != targetColour || _isCellTravelsed(cellCnt) ))
    {
        return;
    }

    m_travelsedCells.push_back(cellCnt);
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

const MatrixStateMatching::MatchedCells_t& MatrixStateMatching::getMatchedCells() const
{
    return m_matchedCells;
}

MatrixStateMatching::MatchedCells_t& MatrixStateMatching::getMatchedCells()
{
    return m_matchedCells;
}

void MatrixStateMatching::stateEnter()
{
    m_matchedCells.clear();

    // get previous state for retrieving the hit result from it
    const MatrixStateIdle* stateIdle = static_cast<const MatrixStateIdle*>(m_matrixController->getState(MatrixStateType::Idle));
    CCTouch* touch = stateIdle->getTouch();

    if (touch)
    {
        CellContainer* hitCell = m_matrixController->getCellAtTouchPoint(touch->getLocation());

        if (hitCell)
        {
            _floodFill(hitCell, hitCell->getColour(), m_matchedCells);

            if (m_matchedCells.size() >= 3)
            {
                m_status = IMatrixState::Status::Finished;
            }
            else
            {
                m_status = IMatrixState::Status::Finished; // TEMP
            }

            m_travelsedCells.clear();
        }
    }
}

void MatrixStateMatching::stateLeave()
{

}

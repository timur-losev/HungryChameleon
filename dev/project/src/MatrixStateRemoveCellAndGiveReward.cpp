#include "Precompiled.h"
#include "MatrixStateRemoveCellAndGiveReward.h"

#include "MatrixController.h"

#include "CellContainer.h"
#include "Cell.h"

#include "MatrixStateMatching.h"


MatrixStateRemoveCellAndGiveReward::MatrixStateRemoveCellAndGiveReward(MatrixController* ctr):
IMatrixState(ctr, MatrixStateType::RemoveCellAndGiveReward)
{

}

MatrixStateRemoveCellAndGiveReward::~MatrixStateRemoveCellAndGiveReward()
{

}

void MatrixStateRemoveCellAndGiveReward::update(float dt)
{

}

IMatrixState::Status::Enum MatrixStateRemoveCellAndGiveReward::getStatus() const
{
    return IMatrixState::Status::Finished;
}

void MatrixStateRemoveCellAndGiveReward::stateEnter()
{
    MatrixStateMatching* stateMatching = static_cast<MatrixStateMatching*>(m_matrixController->getState(MatrixStateType::SearchForMatches));
    MatrixStateMatching::MatchedCells_t& matched = stateMatching->getMatchedCells();

    for (CellContainer* cell : matched)
    {
        cell->deleteCell();
    }
}

void MatrixStateRemoveCellAndGiveReward::stateLeave()
{

}

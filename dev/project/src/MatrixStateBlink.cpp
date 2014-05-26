#include "Precompiled.h"
#include "MatrixStateBlink.h"

#include "MatrixController.h"

#include "MatrixStateMatching.h"

#include "CellContainer.h"

MatrixStateBlink::MatrixStateBlink(MatrixController* ctrl) : IMatrixState(ctrl, MatrixStateType::Blink)
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

void MatrixStateBlink::stateEnter()
{
    CCBlink* blinkAct = CCBlink::create(0.4f, 1);
    MatrixStateMatching::MatchedCells_t& cells = (static_cast<MatrixStateMatching*>(m_matrixController->getState(MatrixStateType::SearchForMatches)))->getMatchedCells();

    hc_foreach(cells, iter)
    {
        (*iter)->runAction(CCBlink::create(0.4f, 1));
    }
}

void MatrixStateBlink::stateLeave()
{

}

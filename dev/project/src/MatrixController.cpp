#include "Precompiled.h"
#include "MatrixController.h"
#include "IMatrixState.h"
#include "CellContainer.h"
#include "Cell.h"
#include "MatrixStateMoving.h"

MatrixController::MatrixController()
{
}

MatrixController::~MatrixController()
{
}

void MatrixController::update(float dt)
{
    if (m_currentState)
    {
        m_currentState->update(dt);
        if (m_currentState->isFinished())
        {
            _popState();
        }
    }
    else
    {
        _popState();
    }
}

void MatrixController::_popState()
{
    delete m_currentState;
    m_currentState = nullptr;

    if (m_stateQueue.empty())
    {
        IMatrixState* state = new MatrixStateMoving();
        pushState(state);
    }
    m_currentState = m_stateQueue.front();
    m_currentState->init(this);
    m_stateQueue.pop();
}

void MatrixController::pushState(IMatrixState* state)
{
    m_stateQueue.push(state);
}

bool MatrixController::init(float cellWidth, float cellHeight)
{
    scheduleUpdate();
    m_cellHeight = cellHeight;
    m_cellWidth = cellWidth;
    //m_spriteDimentsion[byX] = m_cellWidth;
    //m_spriteDimentsion[byY] = m_cellHeight;

    const CCPoint size = ccp(cellWidth, cellHeight);
    CCPoint pos = ccp(0, 0);

    for (uint32_t i = 0; i < MatrixVisibleLineSize; ++i)
    {
        pos.x = i * cellWidth;
        m_matrix.resize(MatrixVisibleLineSize);
        for (uint32_t j = 0; j < MatrixVisibleLineSize; ++j)
        {
            pos.y = j * cellHeight;
            CellContainer* cellC = new CellContainer;
            cellC->generateRandomCell(size);
            cellC->setPosition(pos);
            addChild(cellC);
            m_matrix[i].push_back(cellC);
        }
    }
    return true;
}

void MatrixController::ccTouchMoved(CCTouch *touch, CCEvent *pEvent)
{
    TouchMoved(touch, pEvent);
}

bool MatrixController::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    TouchBegan(touch, pEvent);
    return true;
}

void MatrixController::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    TouchEnded(touch, pEvent);
}

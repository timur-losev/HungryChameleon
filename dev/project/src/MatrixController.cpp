#include "Precompiled.h"
#include "MatrixController.h"
#include "IMatrixState.h"
#include "CellContainer.h"
#include "Cell.h"

#include "MatrixStateMoving.h"
#include "MatrixStateMatching.h"
#include "MatrixStateBlink.h"
#include "MatrixStateRemoveCellAndGiveReward.h"
#include "MatrixStateFillCells.h"

#include "MatrixStateIdle.h"

MatrixController::MatrixController()
{
    m_matrixStates.resize(MatrixStateType::__Total);

    IMatrixState* idle     = new MatrixStateIdle(this);
    IMatrixState* matching = new MatrixStateMatching(this);
    IMatrixState* blink    = new MatrixStateBlink(this);
    IMatrixState* removeCellsAndGiveReward = new MatrixStateRemoveCellAndGiveReward(this);
    IMatrixState* fillCells = new MatrixStateFillCells(this);

    m_matrixStates[MatrixStateType::Idle] = idle;
    m_matrixStates[MatrixStateType::SearchForMatches] = matching;
    m_matrixStates[MatrixStateType::Blink] = blink;
    m_matrixStates[MatrixStateType::RemoveCellAndGiveReward] = removeCellsAndGiveReward;
    m_matrixStates[MatrixStateType::FillCells] = fillCells;

    // build states table
    idle->next = matching;
    matching->other = blink; // matching state has an additional way when matching done, but not enough cells found
    matching->prev = idle;
    blink->next = idle;

    matching->next = removeCellsAndGiveReward;
    removeCellsAndGiveReward->next = fillCells;
    removeCellsAndGiveReward->prev = matching;
    fillCells->next = idle;
    fillCells->prev = removeCellsAndGiveReward;

    m_currentState = idle;
}

MatrixController::~MatrixController()
{
    for (uint32_t i = 0; i < totalWidth(); ++i)
    {
        for (uint32_t j = 0; j < totalHeight(); ++j)
        {
            delete m_matrix[i][j];
        }
    }

    hc_foreach(m_matrixStates, iter)
    {
        delete *iter;
    }
}

void MatrixController::update(float dt)
{
    if (m_currentState)
    {
        m_currentState->update(dt);
        if (m_currentState->getStatus() == IMatrixState::Status::Finished)
        {
            assert(m_currentState->next);

            m_currentState->stateLeave();
            m_currentState = m_currentState->next;
            m_currentState->stateEnter();
        }
        else if (m_currentState->getStatus() == IMatrixState::Status::Other)
        {
            assert(m_currentState->other);

            m_currentState->stateLeave();
            m_currentState = m_currentState->other;
            m_currentState->stateEnter();
        }

    }
    else
    {
        _advanceState();
    }
}

void MatrixController::_advanceState()
{

}

void MatrixController::_changeState(IMatrixState* state)
{
    m_currentState = state;
}

bool MatrixController::init(float cellWidth, float cellHeight)
{
    scheduleUpdate();
    m_cellSize = CCSizeMake(cellWidth, cellHeight);
    //m_spriteDimentsion[byX] = m_cellWidth;
    //m_spriteDimentsion[byY] = m_cellHeight;

    CCPoint pos = ccp(0, 0);
#if 0
    m_matrix.resize(totalWidth());
    for (uint32_t i = 0; i < totalWidth(); ++i)
    {
        m_matrix[i].resize(totalHeight());
        pos.x = (i - (float)additionalWidth()) * cellWidth;
        for (uint32_t j = 0; j < totalHeight(); ++j)
        {
            bool leftBottomQuad = (i < additionalWidth()) && (j < additionalHeight());
            bool leftTopQuad = (i < additionalWidth()) && (j >= additionalHeight() + visibleHeight());
            bool rightBottomQuad = (i >= additionalWidth() + visibleWidth()) && (j <additionalHeight());
            bool rightTopQuad = (i >= additionalWidth() + visibleWidth()) && (j >= additionalHeight() + visibleHeight());

            if (leftBottomQuad || leftTopQuad || rightBottomQuad || rightTopQuad)
            {
                m_matrix[i][j] = nullptr;
                continue;
            }

            pos.y = (j - (float)additionalHeight()) * cellHeight;
            CellContainer* cellC = new CellContainer;
            addChild(cellC);
            cellC->setPosition(pos);
            cellC->generateRandomCell(size);
            cellC->colId = i;
            cellC->rowId = j;
            m_matrix[i][j] = cellC;
        }
    }
#else
    m_matrix.resize(totalWidth());
    for (uint32_t i = 0; i < totalWidth(); ++i)
    {
        m_matrix[i].resize(totalHeight());

        pos.x = i * cellWidth;

        for (uint32_t j = 0; j < totalHeight(); ++j)
        {
            pos.y = j * cellHeight;
            CellContainer* cellC = new CellContainer;
            addChild(cellC);
            cellC->setPosition(pos);
            cellC->generateRandomCell(m_cellSize);
            cellC->colId = i;
            cellC->rowId = j;
            m_matrix[i][j] = cellC;
        }
    }
#endif


    for (uint32_t i = 0; i < totalWidth(); ++i)
    {
        for (uint32_t j = 0; j < totalHeight(); ++j)
        {
            if (i > 0)
            {
                m_matrix[i][j]->setLeft(m_matrix[i - 1][j]);
            }
            if (i < totalWidth() - 1)
            {
                m_matrix[i][j]->setRight(m_matrix[i + 1][j]);
            }
            if (j > 0)
            {
                m_matrix[i][j]->setDown(m_matrix[i][j - 1]);
            }
            if (j < totalHeight() - 1)
            {
                m_matrix[i][j]->setUp(m_matrix[i][j + 1]);
            }
        }
    }
    return true;
}

void MatrixController::ccTouchMoved(CCTouch *touch, CCEvent *pEvent)
{
    m_onTouchMoved(touch, pEvent);
}

bool MatrixController::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    m_onTouchBegan(touch, pEvent);
    return true;
}

void MatrixController::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    m_onTouchEnded(touch, pEvent);
}

MatrixController::Matrix_t& MatrixController::getMatrix()
{
    return m_matrix;
}

const IMatrixState* MatrixController::getState(MatrixStateType::Enum e) const
{
    return m_matrixStates[e];
}

IMatrixState* MatrixController::getState(MatrixStateType::Enum e)
{
    return m_matrixStates[e];
}

CellContainer* MatrixController::getCellAtTouchPoint(const CCPoint& touchLocation) const
{
    CCNode* cellField = m_matrix[0][0]->getParent();

    // Sweep visible rectangle
    uint32_t iMin = additionalWidth();
    uint32_t iMax = iMin + visibleWidth();
    uint32_t jMin = additionalHeight();
    uint32_t jMax = jMin + visibleHeight();

    for (uint32_t i = iMin; i < iMax; ++i)
    {
        for (uint32_t j = jMin; j < jMax; ++j)
        {
            CCPoint pos = m_matrix[i][j]->getPosition();
            CCPoint touch = cellField->convertToNodeSpace(touchLocation);
            CCRect cellBounds(pos.x, pos.y, m_cellSize.width, m_cellSize.height);
            if (cellBounds.containsPoint(touch))
            {
                return m_matrix[i][j];
            }
        }
    }

    return nullptr;
}

const CCSize& MatrixController::getCellSize() const
{
    return m_cellSize;
}

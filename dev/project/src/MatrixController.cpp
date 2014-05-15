#include "Precompiled.h"
#include "MatrixController.h"
#include "IMatrixState.h"
#include "CellContainer.h"
#include "Cell.h"

#include "MatrixStateMoving.h"
#include "MatrixStateMatching.h"

#include "MatrixStateIdle.h"

MatrixController::MatrixController()
{
    m_matrixStates[MatrixSateType::Idle]                = new MatrixStateIdle(this);
    m_matrixStates[MatrixSateType::SearchForMatches]    = new MatrixStateMatching(this);

    m_currentState = m_matrixStates[MatrixSateType::Idle];
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
}

void MatrixController::update(float dt)
{
    if (m_currentState)
    {
        m_currentState->update(dt);
        if (m_currentState->getStatus() == IMatrixState::Status::Finished)
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
    m_currentState = m_matrixStates[MatrixSateType::SearchForMatches];

    /*delete m_currentState;
    m_currentState = nullptr;

    if (m_stateQueue.empty())
    {
        IMatrixState* state = new MatrixStateMoving();
        pushState(state);
    }
    m_currentState = m_stateQueue.front();
    m_currentState->init(this);
    m_stateQueue.pop();*/
}

void MatrixController::pushState(IMatrixState* state)
{
    //m_stateQueue.push(state);
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

    for (uint32_t i = 0; i < totalWidth(); ++i)
    {
        for (uint32_t j = 0; j < totalHeight(); ++j)
        {
            if (!m_matrix[i][j])
            {
                continue;
            }

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

float MatrixController::getCellWidth() const
{
    return m_cellWidth;
}
float MatrixController::getCellHeight() const
{
    return m_cellHeight;
}

MatrixController::Matrix_t& MatrixController::getMatrix()
{
    return m_matrix;
}

const IMatrixState* MatrixController::getState(MatrixSateType::Enum e) const
{
    MatrixStates_t::const_iterator it = m_matrixStates.find(e);

    if (it != m_matrixStates.end())
    {
        return it->second;
    }

    return nullptr;
}

CellContainer* MatrixController::getCellAtTouchPoint(const CCPoint& touchLocation) const
{
    CCNode* cellField = m_matrix[visibleWidth()][visibleHeight()]->getParent();

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
            CCRect cellBounds(pos.x, pos.y, getCellWidth(), getCellHeight());
            if (cellBounds.containsPoint(touch))
            {
                return m_matrix[i][j];
            }
        }
    }

    return nullptr;
}

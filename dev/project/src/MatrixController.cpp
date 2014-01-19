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
            cellC->generateRandomCell(size);
            cellC->setPosition(pos);
            cellC->colId = i;
            cellC->rowId = j;
            addChild(cellC);
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

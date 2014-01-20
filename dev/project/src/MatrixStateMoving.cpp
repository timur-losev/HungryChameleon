#include "Precompiled.h"
#include "MatrixStateMoving.h"
#include "CellField.h"
#include "MatrixController.h"
#include "CellContainer.h"
#include "Cell.h"
#include "MatrixStateMatching.h"

#define ALLOW_DIRECTION_CHANGE 0

MatrixStateMoving::MatrixStateMoving()
{

}

MatrixStateMoving::~MatrixStateMoving()
{
}

void MatrixStateMoving::update(float dt)
{

}

bool MatrixStateMoving::isFinished()
{
    return m_isFinished;
}

void MatrixStateMoving::init(MatrixController* controller)
{
    controller->TouchBegan.connect(this, &MatrixStateMoving::touchBegan);
    controller->TouchEnded.connect(this, &MatrixStateMoving::touchEnded);
    controller->TouchMoved.connect(this, &MatrixStateMoving::touchMoved);
    m_controller = controller;
}

void MatrixStateMoving::touchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_touch)
    {
        m_touch = pTouch;
        if(!_findHitCell())
            m_touch = nullptr;
    }
}

void MatrixStateMoving::touchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_touch == pTouch)
    {
        _Finalize();
    }
}

void MatrixStateMoving::touchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_touch == pTouch)
    {
        _updateDirection();
        _updatePositions();
    }
}

void MatrixStateMoving::_Finalize()
{
    CCPoint delta = ccpSub(m_touch->getLocation(), m_touch->getStartLocation());

    IMatrixState* matching = new MatrixStateMatching();
    m_controller->pushState(matching);

    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
    int steps = 0;
    if (m_direction == byX)
    {
        float fstep = delta.x / m_controller->getCellWidth();
        fstep += (fstep > 0) ? 0.5 : -0.5;
        steps = int(fstep);
    }
    else if (m_direction == byY)
    {
        float fstep = delta.y / m_controller->getCellHeight();
        fstep += (fstep > 0) ? 0.5 : -0.5;
        steps = int(fstep);
    }


    // Clear additional offset
    for (uint32_t i = 0; i < m_controller->totalWidth(); ++i)
    {
        for (uint32_t j = 0; j < m_controller->totalHeight(); ++j)
        {
            if (matrix[i][j])
                matrix[i][j]->setAdditionalOffset(ccp(0, 0));
        }
    }
    _shiftMatrixElements(m_hitCell->colId, m_hitCell->rowId, steps, m_direction);

    m_isFinished = true;
}

bool MatrixStateMoving::_findHitCell()
{
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
    CCNode* cellField = matrix[m_controller->visibleWidth()][m_controller->visibleHeight()]->getParent();

    // Sweep visible rectangle
    int iMin = m_controller->additionalWidth();
    int iMax = iMin + m_controller->visibleWidth();
    int jMin = m_controller->additionalHeight();
    int jMax = jMin + m_controller->visibleHeight();

    for (uint32_t i = iMin; i < iMax; ++i)
    {
        for (uint32_t j = jMin; j < jMax; ++j)
        {
            CCPoint pos = matrix[i][j]->getPosition();
            CCPoint touch = cellField->convertTouchToNodeSpace(m_touch);
            CCRect cellBounds(pos.x, pos.y, m_controller->getCellWidth(), m_controller->getCellHeight());
            if (cellBounds.containsPoint(touch))
            {
                m_hitCell = matrix[i][j];
                return true;
            }
        }
    }  
    return false;
}

void MatrixStateMoving::_updateDirection()
{
    assert(m_touch);
#if !ALLOW_DIRECTION_CHANGE
    if(m_direction != byNone)
        return;
#endif
    CCPoint delta = ccpSub(m_touch->getLocation(), m_touch->getStartLocation());
    if (abs(delta.x) > abs(delta.y))
    {
        m_direction = byX;
    }
    else
    {
        m_direction = byY;
    }
}

void MatrixStateMoving::_updatePositions()
{
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
#if ALLOW_DIRECTION_CHANGE
    for (uint32_t i = 0; i < MatrixController::MatrixVisibleLineSize; ++i)
    {
        for (uint32_t j = 0; j < MatrixController::MatrixVisibleLineSize; ++j)
        {
            matrix[i][j]->setAdditionalOffset(ccp(0, 0));
        }
    }
#endif
    CCPoint delta = ccpSub(m_touch->getLocation(), m_touch->getStartLocation());
    if (m_direction == byX)
    {
        int row = m_hitCell->rowId;
        for (uint32_t i = 0; i < m_controller->totalWidth(); ++i)
        {
            if (matrix[i][row])
                matrix[i][row]->setAdditionalOffset(ccp(delta.x, 0));
        }
    }
    else
    {
        int col = m_hitCell->colId;
        for (uint32_t i = 0; i < m_controller->totalHeight(); ++i)
        {
            if (matrix[col][i])
                matrix[col][i]->setAdditionalOffset(ccp(0, delta.y));
        }
    }
}

void MatrixStateMoving::_shiftMatrixElements(int cellColumn, int cellRow, int steps, Direction dir)
{
    CCPoint cellSize(m_controller->getCellWidth(), m_controller->getCellHeight());
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
    if (dir == byX)
    {
        for (int step = 0; step < abs(steps); ++step)
        {
            if (steps < 0)
            {
                for (int col = 1; col < m_controller->totalWidth(); ++col)
                {
                    if (matrix[col - 1][cellRow] && (**matrix[col][cellRow]))
                        (*matrix[col - 1][cellRow]) = matrix[col][cellRow]->pass();
                }
                //matrix[m_controller->visibleWidth() - 1][cellRow]->generateRandomCell(cellSize);
            }
            else
            {
                for (int col = m_controller->totalWidth() - 1; col > 0; --col)
                {
                    if (matrix[col][cellRow] && **matrix[col - 1][cellRow])
                        (*matrix[col][cellRow]) = matrix[col - 1][cellRow]->pass();
                }
                //matrix[0][cellRow]->generateRandomCell(cellSize);
            }
        }
    }
    else if (dir == byY)
    {
        for (int step = 0; step < abs(steps); ++step)
        {
            if (steps < 0)
            {
                for (int row = 1; row < m_controller->totalHeight(); ++row)
                {
                    if (matrix[cellColumn][row - 1] && **matrix[cellColumn][row])
                        (*matrix[cellColumn][row - 1]) = matrix[cellColumn][row]->pass();
                }
                //matrix[cellColumn][m_controller->visibleHeight() - 1]->generateRandomCell(cellSize);
            }
            else
            {
                for (int row = m_controller->totalHeight() - 1; row > 0; --row)
                {
                    if (matrix[cellColumn][row] && **matrix[cellColumn][row - 1])
                        (*matrix[cellColumn][row]) = matrix[cellColumn][row - 1]->pass();
                }
                //matrix[cellColumn][0]->generateRandomCell(cellSize);
            }
        }
    }
}

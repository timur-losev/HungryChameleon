#include "Precompiled.h"
#include "MatrixStateMatching.h"
#include "MatrixController.h"
#include "CellContainer.h"
#include "Cell.h"
#include "MatrixStateRemove.h"

MatrixStateMatching::MatrixStateMatching()
{

}

MatrixStateMatching::~MatrixStateMatching()
{

}

void MatrixStateMatching::update(float dt)
{
    std::list<std::list<CellContainer*> > matchings;
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();

    // Sweep visible rectangle
    uint32_t iMin = m_controller->additionalWidth();
    uint32_t iMax = iMin + m_controller->visibleWidth();
    uint32_t jMin = m_controller->additionalHeight();
    uint32_t jMax = jMin + m_controller->visibleHeight();
    for (uint32_t i = iMin; i < iMax; ++i)
    {
        for (uint32_t j = jMin; j < jMax; ++j)
        {
            if (matrix[i][j] && matrix[i][j]->isDirty())
            {
                std::list<CellContainer*> singleMatching;
                _floodFill(matrix[i][j], (*matrix[i][j])->colour, singleMatching);
                if (singleMatching.size() > 3)
                {
                    matchings.push_back(singleMatching);
                }
            }
        }
    }
    if (matchings.size() > 0)
    {
        IMatrixState* removeState = new MatrixStateRemove(matchings);
        m_controller->pushState(removeState);
    }
    m_isFinished = true;
}

bool MatrixStateMatching::isFinished()
{
	return m_isFinished;
}

void MatrixStateMatching::init(MatrixController* controller)
{
    m_controller = controller;
}

void MatrixStateMatching::_floodFill(CellContainer* c, Cell::Colour targetColour, std::list<CellContainer*>& matchingList)
{
    if (c && ((*c)->travelsed || (*c)->colour != targetColour))
    {
        return;
    }
    (*c)->travelsed = true;
    c->clean();

    matchingList.push_back(c);

    if (c->right() && c->right()->isVisible())
    {
        _floodFill(c->right(), targetColour, matchingList);
    }
    if (c->left() && c->left()->isVisible())
    {
        _floodFill(c->left(), targetColour, matchingList);
    }
    if (c->up() && c->up()->isVisible())
    {
        _floodFill(c->up(), targetColour, matchingList);
    }
    if (c->down() && c->down()->isVisible())
    {
        _floodFill(c->down(), targetColour, matchingList);
    }

#if 0
    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
    int right = c->colId + 1;
    int left = c->colId - 1;
    int up = c->rowId + 1;
    int down = c->rowId - 1;

    if (right < m_controller->visibleWidth())
    {
        _floodFill(matrix[right][c->rowId], targetColour, matchingList);
    }
    if (left >= 0)
    {
        _floodFill(matrix[left][c->rowId], targetColour, matchingList);
    }
    if (up < m_controller->visibleHeight())
    {
        _floodFill(matrix[c->colId][up], targetColour, matchingList);
    }
    if (down >= 0)
    {
        _floodFill(matrix[c->colId][down], targetColour, matchingList);
    }

#endif // 0
}

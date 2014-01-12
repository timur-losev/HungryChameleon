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
    for (uint32_t i = 0; i < MatrixController::MatrixVisibleLineSize; ++i)
    {
        for (uint32_t j = 0; j < MatrixController::MatrixVisibleLineSize; ++j)
        {
            if (matrix[i][j]->isDirty())
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
    if ((*c)->travelsed || (*c)->colour != targetColour)
    {
        return;
    }
    (*c)->travelsed = true;
    c->clean();

    matchingList.push_back(c);

    MatrixController::Matrix_t& matrix = m_controller->getMatrix();
    int right = c->colId + 1;
    int left = c->colId - 1;
    int up = c->rowId + 1;
    int down = c->rowId - 1;

    if (right < MatrixController::MatrixVisibleLineSize)
    {
        _floodFill(matrix[right][c->rowId], targetColour, matchingList);
    }
    if (left >= 0)
    {
        _floodFill(matrix[left][c->rowId], targetColour, matchingList);
    }
    if (up < MatrixController::MatrixVisibleLineSize)
    {
        _floodFill(matrix[c->colId][up], targetColour, matchingList);
    }
    if (down >= 0)
    {
        _floodFill(matrix[c->colId][down], targetColour, matchingList);
    }
}

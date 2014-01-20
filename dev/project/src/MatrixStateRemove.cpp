#include "Precompiled.h"
#include "MatrixStateRemove.h"
#include "CellField.h"
#include "CellContainer.h"
#include "MatrixController.h"
#include "MatrixStateFill.h"

MatrixStateRemove::MatrixStateRemove(std::list<std::list<CellContainer*> > matchings)
    : m_matchings(matchings)
{

}

MatrixStateRemove::~MatrixStateRemove()
{

}

void MatrixStateRemove::update(float dt)
{
    _execute();
}

bool MatrixStateRemove::isFinished()
{
	return m_isFinished;
}

void MatrixStateRemove::init(MatrixController* controller)
{
    m_controller = controller;
}

void MatrixStateRemove::_execute()
{
    if (m_matchings.size() > 0)
    {
        for (std::list<CellContainer*> match : m_matchings)
        {
            for (CellContainer* cell : match)
            {
                cell->deleteCell();
            }
        }
        m_controller->pushState(new MatrixStateFill);
    }
    m_isFinished = true;
}

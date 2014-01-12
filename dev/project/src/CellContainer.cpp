#include "Precompiled.h"
#include "CellContainer.h"
#include "Cell.h"

CellContainer::CellContainer()
{
}


CellContainer::~CellContainer()
{
}

const CellContainer& CellContainer::operator = (Cell* cell)
{
    _releaseCell();
    m_cell = cell;
    addChild(m_cell);
    return *this;
}

Cell* CellContainer::operator -> ()
{
    assert(m_cell);
    return m_cell;
}

void CellContainer::_releaseCell()
{
    if (m_cell)
    {
        removeAllChildren();
        m_cell->release();
        m_cell = nullptr;
    }
}

void CellContainer::generateRandomCell(CCPoint size)
{
    _releaseCell();
    (*this) = Cell::createRandom(size);
}

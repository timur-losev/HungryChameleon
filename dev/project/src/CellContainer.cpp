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
    m_dirty = true;
    _releaseCell();
    m_cell = cell;
    m_cell->travelsed = false;
    addChild(m_cell);
    setAdditionalOffset(ccp(0, 0));
    return *this;
}

Cell* CellContainer::operator -> ()
{
    assert(m_cell);
    return m_cell;
}

Cell* CellContainer::operator * ()
{
    return m_cell;
}

void CellContainer::_releaseCell()
{
    if (m_cell)
    {
        removeChild(m_cell);
        m_cell = nullptr;
    }
}

void CellContainer::generateRandomCell(CCPoint size)
{
    m_center = ccp(size.x / 2, size.y / 2);
    m_dirty = true;
    _releaseCell();
    (*this) = Cell::createRandom(size);
}

Cell* CellContainer::pass()
{
    m_dirty = true;
    Cell* ret = m_cell;
    _releaseCell();
    return ret;
}

bool CellContainer::isDirty()
{
    return m_dirty;
}

void CellContainer::clean()
{
    m_dirty = false;
}

CCPoint CellContainer::getCenterPoint()
{
    return m_center;
}

void CellContainer::setAdditionalOffset(const CCPoint& p)
{
    if (m_cell)
    {
        m_cell->setAdditionalOffset(p);
        CCPoint cellCenter(getCenterPoint() + m_cell->getPosition() + getPosition());
        CCRect parent(0, 0, getParent()->getContentSize().width, getParent()->getContentSize().height);
        if (parent.containsPoint(cellCenter))
        {
            setVisible(true);
        }
        else
        {
            setVisible(false);
        }
    }
}

#pragma once

class Cell;

class CellContainer : public CCNode
{
public:
    CellContainer();
    ~CellContainer();

    const CellContainer&    operator = (Cell*);
    Cell*                   operator -> ();

    void                    generateRandomCell(CCPoint);

private:
    Cell*                   m_cell = nullptr;
    void                    _releaseCell();
};


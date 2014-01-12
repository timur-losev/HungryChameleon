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
    Cell*                   pass();
    bool                    isDirty();
    void                    clean();

    int                     rowId = -1;
    int                     colId = -1;

private:
    Cell*                   m_cell = nullptr;
    void                    _releaseCell();
    bool                    m_dirty = true;
};


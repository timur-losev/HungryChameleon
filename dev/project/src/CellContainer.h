#pragma once

class Cell;

class CellContainer : public CCNode
{
public:
    CellContainer();
    ~CellContainer();

    const CellContainer&    operator = (Cell*);
    Cell*                   operator -> ();
    Cell*                   operator * ();

    void                    generateRandomCell(CCPoint);
    CCPoint&                getCenterPoint();
    Cell*                   pass();
    bool                    isDirty();
    void                    clean();

    int                     rowId = -1;
    int                     colId = -1;
    CellContainer&          left() { return *m_left; }
    CellContainer&          right() { return *m_right; }
    CellContainer&          up() { return *m_up; }
    CellContainer&          down() { return *m_down; }

    void                    setLeft(CellContainer* c) { m_left = c; }
    void                    setRight(CellContainer* c) { m_right = c; }
    void                    setUp(CellContainer* c) { m_up = c; }
    void                    setDown(CellContainer* c) { m_down = c; }

private:
    Cell*                   m_cell = nullptr;
    void                    _releaseCell();
    bool                    m_dirty = true;
    CellContainer*          m_left  = nullptr;
    CellContainer*          m_right = nullptr;
    CellContainer*          m_up    = nullptr;
    CellContainer*          m_down  = nullptr;
    CCPoint                 m_center;
};


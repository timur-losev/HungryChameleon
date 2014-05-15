#pragma once

class Cell;

class CellContainer : public CCNode
{
private:
    Cell*                   m_cell = nullptr;
    void                    _releaseCell();
    bool                    m_dirty = true;
    CellContainer*          m_left = nullptr;
    CellContainer*          m_right = nullptr;
    CellContainer*          m_up = nullptr;
    CellContainer*          m_down = nullptr;
    CCPoint                 m_center;

public:
    CellContainer();
    ~CellContainer();

    //const CellContainer&    operator = (Cell*);

    void                    attachCell(Cell* value);

    Cell*                   operator -> ();
    Cell*                   operator * ();

    void                    generateRandomCell(CCPoint);
    CCPoint                 getCenterPoint();
    Cell*                   pass();
    void                    deleteCell();
    bool                    isDirty();
    void                    clean();

    int                     rowId = -1;
    int                     colId = -1;
    CellContainer*          left() { return m_left; }
    CellContainer*          right() { return m_right; }
    CellContainer*          up() { return m_up; }
    CellContainer*          down() { return m_down; }

    void                    setLeft(CellContainer* c) { m_left = c; }
    void                    setRight(CellContainer* c) { m_right = c; }
    void                    setUp(CellContainer* c) { m_up = c; }
    void                    setDown(CellContainer* c) { m_down = c; }

    void                    setAdditionalOffset(const CCPoint&);
};


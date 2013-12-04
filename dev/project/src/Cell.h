#pragma once

class AnimatedCell;

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/


class Cell : public CCNode
{
public:

    enum Colour
    {
        Undefined,
        Red,
        Brown,
        Green,
        Purple,
        Aqua,
        Blue,
        Yellow,
        Turquoise,
        Black,
        DarkBlue
    };

    Colour color = Undefined;

    int colId = -1;
    int rowId = -1;

    bool markedForRemove = false;

	Cell(Colour c);// : color(c)
    //{
    //}
};


class CellField : public CCLayer
{
public:
    static const uint32_t MatrixVisibleLineSize = 10;
    static const uint32_t MatrixSize = MatrixVisibleLineSize * MatrixVisibleLineSize;
    static const uint32_t CenterMatrixSize = MatrixSize * 5;

private:
    CCPoint m_centerMatrix[CenterMatrixSize];

    typedef std::deque<Cell*> Line_t;

    Line_t m_rows[MatrixVisibleLineSize];
    Line_t m_cols[MatrixVisibleLineSize];

    enum Direction
    {
        byNone = -1,
        byX,
        byY,

        DirectionsCount
    };

    enum Rewind
    {
        ToTheEnd,
        ToTheBegin
    };

    Cell* m_movingCells[DirectionsCount];

    Cell* m_hitCell;

    enum MatrixState
    {
        MSIdle,
        MSMoving,
        MSStucking,
        MSMatching,

        STATES_MAX
    } m_state;

    Direction m_lockedDirection;

    CCPoint   m_lastDelta;

    int       m_stepsCount, m_prevStep;
    float     m_spriteDimentsion[DirectionsCount];
    CCPoint   m_from;

private:

    void         _dragCells(const CCPoint& delta);

    void         _stabilizeMatrix(Line_t &line);

    void         _stuckMovedCells();
    void         _advanceState(MatrixState state);
    Cell*        _next(Cell* cur, Direction dir, const Line_t& line);

    void         _rebaseByX(Cell* sampleCell, Line_t& row);
    void         _rebaseByY(Cell* sampleCell, Line_t& col);

    void         _removeCellIfPossible(Cell* cell);
    void         _removeCell(Cell* cell);

    Cell*        _createRandomCell();

    Line_t&      _getLineByDirection(Cell* hitcell, Direction dir);

    inline float _getPointFieldByDirection(const CCPoint& p) const
    {
        return *(&p.x + m_lockedDirection);
    }

    MatrixState  _getState() const;
	
	void		_onCellRemoved(Cell* cell);
public:

    CellField();
    ~CellField();

    virtual bool init();

    void         onTouchReleased(CCTouch* touch);
    void         onTouchPressed(CCTouch* touch);
    void         onTouchMoved(CCTouch* touch);

    void         onUpdate(float dt);
};
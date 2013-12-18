#pragma once
#include "Cell.h"

class AnimatedCell;

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/

class CellField : public CCLayer
{
public:
    static const uint32_t MatrixVisibleLineSize = 10;
    static const uint32_t MatrixSize = MatrixVisibleLineSize * MatrixVisibleLineSize;
    static const uint32_t CenterMatrixSize = MatrixSize * 5;

private:
    CCPoint m_centerMatrix[CenterMatrixSize];

    typedef std::deque<Cell*> Line_t;
	typedef std::list<Cell*> CellList_t;

    Line_t m_rows[MatrixVisibleLineSize];
    Line_t m_cols[MatrixVisibleLineSize];

    enum Direction
    {
        byNone = -1,
        byX,
        byY,

        DirectionsCount
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

	float     m_cellWidth;
	float     m_cellHeight;

private:
	Cell*		 _randomCell();
    void         _dragCells(const CCPoint& delta);

    void         _stabilizeMatrix(Line_t &line);

    void         _matchingState();
	void		 _fallDownState(const std::list<CellList_t>& matchedCells);

    void         _stuckMovedCells();
    void         _advanceState(MatrixState state);
    Cell*        _next(Cell* cur, Direction dir, const Line_t& line);

    void         _rebaseByX(Cell* sampleCell, Line_t& row);
    void         _rebaseByY(Cell* sampleCell, Line_t& col);

    void         _removeCellIfPossible(Cell* cell);
    void         _removeCell(Cell* cell);

    void         _moveColumnFragmenDown(uint32_t columnIndex, uint32_t startingFromRow, uint32_t numberOfPositions);

    Cell*        _createRandomCell();

    Line_t&      _getLineByDirection(Cell* hitcell, Direction dir);

    inline float _getPointFieldByDirection(const CCPoint& p) const
    {
        return *(&p.x + m_lockedDirection);
    }

    MatrixState  _getState() const;
	void         _floodFill(Cell* cell, Cell::Colour targetColour, std::list<Cell*>& matchingList) const;

	void		_onCellRemoved(Cell* cell);
public:

    CellField();
    ~CellField();

    virtual bool init(float cellWidth, float cellHeight);

	bool		 ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void		 ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void		 ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    void         onUpdate(float dt);
};
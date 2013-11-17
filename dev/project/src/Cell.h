#pragma once


/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/


class Cell : public CCSprite
{
public:

    Cell* up = nullptr;
    Cell* down = nullptr;
    Cell* next = nullptr;
    Cell* prev = nullptr;

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

    Cell(Colour c) : color(c)
    {
    }
};


class CellField : public CCLayer
{
private:
    static const uint32_t MatrixLineSize = 10;
    static const uint32_t MatrixSize = MatrixLineSize * MatrixLineSize;

    CCPoint m_centerMatrix[MatrixSize];

    enum Direction
    {
        byNone = -1,
        byX,
        byY,

        DirectionsCount
    };

    Cell* m_movingData[DirectionsCount][MatrixLineSize];

    enum MatrixState
    {
        MSIdle,
        MSMoving,
        MSStucking,
        MSStabilization,
        MSMatching,

        STATES_MAX
    } m_state;

    Direction m_lockedDirection;

    CCPoint   m_lastDelta;
    float     m_inertia;
    bool      m_inertiaInUse;

private:

    void         _dragCells(const CCPoint& delta);
    void         _applyInertia(float value);
    void         _stuckMovedCells();
    void         _stabilizationState();
    void         _advanceState(MatrixState state);

    inline float _getPointFieldByDirection(const CCPoint& p) const
    {
        return *(&p.x + m_lockedDirection);
    }

    MatrixState  _getState() const;

public:

    CellField();
    ~CellField();

    virtual bool init();

    void         onTouchReleased(CCTouch* touch);
    void         onTouchPressed(CCTouch* touch);
    void         onTouchMoved(CCTouch* touch);

    void         onUpdate(float dt);
};
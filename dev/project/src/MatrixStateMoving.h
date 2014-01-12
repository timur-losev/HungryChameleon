#pragma once
#include "IMatrixState.h"

class CellContainer;
class MatrixController;

class MatrixStateMoving : public IMatrixState, public has_slots<>
{
public:
    enum Direction
    {
        byNone = -1,
        byX,
        byY,

        DirectionsCount
    };

public:
	MatrixStateMoving();
	virtual ~MatrixStateMoving();

    virtual void        update(float dt);
    virtual bool        isFinished();
    virtual void        init(MatrixController*);

private:
    void		        touchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void		        touchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void		        touchMoved(CCTouch *pTouch, CCEvent *pEvent);

private:
    void                _Finalize();
    void                _findHitCell();
    void                _updateDirection();
    void                _updatePositions();
    void                _shiftMatrixElements(int column, int row, int steps, Direction dir);

private:
    bool                m_isFinished = false;
    MatrixController*   m_controller = nullptr;
    Direction           m_direction = byNone;
    CCTouch*            m_touch = nullptr;
    CellContainer*      m_hitCell = nullptr;
};

#pragma once
#include "IMatrixState.h"
#include "CellField.h"

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
    void		        TouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void		        TouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void		        TouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    void                Finalize();

private:
    bool                m_isFinished = false;
    MatrixController*   m_controller = nullptr;
    Direction           m_direction = byNone;
};

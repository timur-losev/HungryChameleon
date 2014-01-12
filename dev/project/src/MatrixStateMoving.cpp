#include "Precompiled.h"
#include "MatrixStateMoving.h"
#include "CellField.h"
#include "MatrixController.h"

MatrixStateMoving::MatrixStateMoving()
{

}

MatrixStateMoving::~MatrixStateMoving()
{
}

void MatrixStateMoving::update(float dt)
{

}

bool MatrixStateMoving::isFinished()
{
    return m_isFinished;
}

void MatrixStateMoving::init(MatrixController* controller)
{
    controller->TouchBegan.connect(this, &MatrixStateMoving::TouchBegan);
    controller->TouchEnded.connect(this, &MatrixStateMoving::TouchEnded);
    controller->TouchMoved.connect(this, &MatrixStateMoving::TouchMoved);
}

void MatrixStateMoving::TouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    int a = 0;
}

void MatrixStateMoving::TouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    Finalize();
}

void MatrixStateMoving::TouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void MatrixStateMoving::Finalize()
{
    m_isFinished = true;
}

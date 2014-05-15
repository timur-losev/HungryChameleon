#pragma once

class MatrixControllerEvents
{
public:
    typedef signal2<CCTouch*, CCEvent*> OnTouchBegan_t;
    typedef signal2<CCTouch*, CCEvent*> OnTouchEnded_t;
    typedef signal2<CCTouch*, CCEvent*> OnTouchMoved_t;
};
#pragma once
#include "Cell.h"
/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
    */


class AnimatedCell : public Cell
{
public:

    AnimatedCell(Colour, CCPoint);
    void onEnterFinish(extension::CCBone *, const char *, int, int);
    //void onEnter();
    void onEnterTransitionDidFinish();
};


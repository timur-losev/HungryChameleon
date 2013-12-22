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

    Colour colour = Undefined;

    int colId = -1;
    int rowId = -1;

    bool markedForRemove = false;
    bool travelsed = false;

    Cell(Colour c, CCPoint size);
	virtual ~Cell() {};

	static Cell* createRandom(CCPoint size);

	void SetDebugInfo(int, int);
	virtual void onEnterTransitionDidFinish() {}
};
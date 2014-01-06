#pragma once
#include "IMatrixState.h"
#include "CellField.h"


class MatrixStateMoving : public IMatrixState
{
public:
	MatrixStateMoving();
	virtual ~MatrixStateMoving();

    virtual void update(float dt);
	virtual bool isFinished();
};

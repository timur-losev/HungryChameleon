#pragma once
#include "IMatrixState.h"

class MatrixStateFill : public IMatrixState
{
public:
	MatrixStateFill();
	virtual ~MatrixStateFill();

    virtual void update(float dt);
	virtual bool isFinished();
};

#pragma once
#include "IMatrixState.h"

class MatrixStateRemove : public IMatrixState
{
public:
	MatrixStateRemove();
	virtual ~MatrixStateRemove();

    virtual void update(float dt);
	virtual bool isFinished();
};

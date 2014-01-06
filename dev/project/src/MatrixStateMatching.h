#pragma once
#include "IMatrixState.h"

class MatrixStateMatching : public IMatrixState
{
public:
	MatrixStateMatching();
	virtual ~MatrixStateMatching();

    virtual void update(float dt);
	virtual bool isFinished();
};

#pragma once
#include "IMatrixState.h"

class CellContainer;
class MatrixController;

class MatrixStateRemove : public IMatrixState
{
public:
	MatrixStateRemove(std::list<std::list<CellContainer*> >);
	virtual ~MatrixStateRemove();

    virtual void update(float dt);
	virtual bool isFinished();
    virtual void init(MatrixController*);
};

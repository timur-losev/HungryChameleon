#pragma once
#include "IMatrixState.h"

class MatrixController;
class CellContainer;

class MatrixStateFill : public IMatrixState
{
public:
	MatrixStateFill();
	virtual ~MatrixStateFill();

    virtual void update(float dt);
	virtual bool isFinished();
    virtual void init(MatrixController*);
    virtual void reset() {}

private:
    void            _execute();
    void            _dropDown(CellContainer*);

private:
    MatrixController* m_controller = nullptr;
    bool m_isFinished = false;
};

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

private:
    void _execute();

private:
    MatrixController* m_controller = nullptr;
    std::list<std::list<CellContainer*> > m_matchings;
    bool m_isFinished = false;
};

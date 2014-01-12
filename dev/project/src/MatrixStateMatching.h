#pragma once
#include "IMatrixState.h"
#include "Cell.h"

class MatrixController;
class CellContainer;

class MatrixStateMatching : public IMatrixState
{
public:
	MatrixStateMatching();
	virtual ~MatrixStateMatching();

    virtual void        update(float dt);
    virtual bool        isFinished();
    virtual void        init(MatrixController*);

private:
    void                _floodFill(CellContainer*, Cell::Colour targetColour, std::list<CellContainer*>&);
    MatrixController*   m_controller = nullptr;
    bool                m_isFinished = false;
};

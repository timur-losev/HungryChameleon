#pragma once

#include "IMatrixState.h"
#include "Cell.h"

class CellContainer;

class MatrixStateMatching : public IMatrixState
{
public:
    typedef std::list<CellContainer*> MatchedCells_t;

private:
    void                _floodFill(CellContainer*, Cell::Colour targetColour, MatchedCells_t&);
    bool                m_isFinished;

    MatchedCells_t      m_matchedCells;

public:
    MatrixStateMatching(MatrixController*);
    virtual ~MatrixStateMatching();

    virtual void        update(float dt) override;
    virtual IMatrixState::Status::Enum     getStatus() const override;
    virtual void        reset() override;
};

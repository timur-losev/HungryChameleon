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
    bool                _isCellTravelsed(CellContainer*);

    MatchedCells_t      m_matchedCells;
    MatchedCells_t      m_travelsedCells;
    IMatrixState::Status::Enum m_status;

public:
    MatrixStateMatching(MatrixController*);
    virtual ~MatrixStateMatching();

    virtual void        update(float dt) override;
    virtual IMatrixState::Status::Enum     getStatus() const override;
    virtual void        stateEnter() override;
    virtual void        stateLeave() override;

    const MatchedCells_t&     getMatchedCells() const;
    MatchedCells_t&           getMatchedCells();
};

#pragma once
#include "CellFieldBaseState.h"

class CellFieldStateIdle : public CellFieldBaseState
{
public:
    CellFieldStateIdle();
    virtual ~CellFieldStateIdle();

    virtual void update(float dt);
};

#pragma once

class CellFieldBaseState
{
public:
    CellFieldBaseState();
    virtual ~CellFieldBaseState();

    virtual void update(float dt);
};

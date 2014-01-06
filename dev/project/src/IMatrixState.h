#pragma once

class IMatrixState
{
public:
	IMatrixState();
	virtual ~IMatrixState();

    virtual void update(float dt) = 0;
	virtual bool isFinished() = 0;
};

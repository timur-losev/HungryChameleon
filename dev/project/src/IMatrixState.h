#pragma once

class MatrixController;

class IMatrixState
{
public:
	IMatrixState();
	virtual ~IMatrixState();

    virtual void update(float dt) = 0;
	virtual bool isFinished() = 0;
    virtual void init(MatrixController*) {};
};

#include "Precompiled.h"
#include "MatrixStateRemove.h"
#include "CellField.h"


MatrixStateRemove::MatrixStateRemove(std::list<std::list<CellContainer*> > matchings)
    : m_matchings(matchings)
{

}

MatrixStateRemove::~MatrixStateRemove()
{

}

void MatrixStateRemove::update(float dt)
{
    _execute();
}

bool MatrixStateRemove::isFinished()
{
	return true;
}

void MatrixStateRemove::init(MatrixController* controller)
{
    m_controller = controller;
}

void MatrixStateRemove::_execute()
{
    
}

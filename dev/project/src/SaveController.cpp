#include "Precompiled.h"

#include "SaveController.h"

const char* SaveController::s_saveFile = "save.dat";

SaveController::SaveController()
{

}

SaveController::~SaveController()
{

}

SaveController* SaveController::createController()
{
	SaveController* pRet = new SaveController();
	if (pRet != NULL)
	{
		pRet->autorelease();
	}
	return pRet;
}

void SaveController::save()
{

}

bool SaveController::load()
{
	return true;
}

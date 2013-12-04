#include "Precompiled.h"
#include "AnimatedCell.h"

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
    */

AnimatedCell::AnimatedCell(Colour c) : Cell(c)
{
	if (c == Red)
	{
		removeAllChildren();
		extension::CCArmature *armature = extension::CCArmature::create("spider");
		armature->setScale(0.1f);
		float speed = static_cast<float>(rand() % 10);
		speed /= 20;
		speed += 0.75;
		armature->getAnimation()->setSpeedScale(speed);
		armature->getAnimation()->playByIndex(0);
		armature->setAnchorPoint(ccp(0, 0));
		armature->setPosition(-25, -12);
		addChild(armature, 2);
	}
}
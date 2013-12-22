#include "Precompiled.h"
#include "AnimatedCell.h"

using namespace extension;

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
    */

AnimatedCell::AnimatedCell(Colour c, CCPoint s) : Cell(c, s)
{
	if (c == Red)
	{
		removeAllChildren();
		CCArmature *armature = CCArmature::create("spider");
		armature->setScale(0.1f);
		float speed = static_cast<float>(rand() % 10);
		speed /= 20;
		speed += 0.75;
		armature->getAnimation()->setSpeedScale(speed);
		armature->setVisible(false);
		addChild(armature, 2);
		armature->setAnchorPoint(ccp(0, 0));
		armature->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(AnimatedCell::onEnterFinish));
		armature->setPosition(-25, -12);
	}
}

void AnimatedCell::onEnterFinish(CCBone* bone, const char* name, int, int)
{
	if (!strcmp("enter_finished", name))
	{
		bone->getArmature()->getAnimation()->play("idle");
	}
}

void AnimatedCell::onEnterTransitionDidFinish()
{

	CCArmature* armature = dynamic_cast<CCArmature*>(getChildren()->lastObject());
	if (armature)
	{
		armature->getAnimation()->play("enter");
		armature->setVisible(true);
	}
}

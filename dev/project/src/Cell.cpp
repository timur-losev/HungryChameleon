#include "Precompiled.h"
#include "Cell.h"
#include "CellField.h"
#include "AnimatedCell.h"

// particle system test
#include "particle_nodes/CCParticleSystem.h"

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
    */

//static CCTexture2D* tex = nullptr;

static std::pair<const char*, Cell::Colour> SpriteDefines[] =
{
    std::make_pair("red.png", Cell::Undefined),

    std::make_pair("red.png", Cell::Red),
    std::make_pair("brown.png", Cell::Brown),
    std::make_pair("green.png", Cell::Green),
    std::make_pair("purple.png", Cell::Purple),
    std::make_pair("aqua.png", Cell::Aqua),
    std::make_pair("blue.png", Cell::Blue),
    std::make_pair("yellow.png", Cell::Yellow)
};

Cell::Cell(Colour c)
: colour(c)
{
	auto& pair = SpriteDefines[c];

    
    CCSprite* a = CCSprite::createWithSpriteFrameName(pair.first);
	a->setAnchorPoint(ccp(0, 0));
	addChild(a);
}

Cell* Cell::createRandom()
{
    int id = rand() % 7 + 1;

    auto& pair = SpriteDefines[id];

	Cell* cell = new AnimatedCell(pair.second);

    return cell;
}

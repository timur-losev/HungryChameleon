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

Cell::Cell(Colour c, CCPoint size)
: colour(c)
{
    auto& pair = SpriteDefines[c];
    CCSprite* a = CCSprite::createWithSpriteFrameName(pair.first);
    a->setAnchorPoint(ccp(0, 0));
    addChild(a);
    const CCRect currentSize = a->getTextureRect();
    float scale = std::max(size.x / currentSize.getMaxX(), size.y / currentSize.getMaxY());
    setScale(scale);
}

Cell* Cell::createRandom(CCPoint size)
{
    int id = rand() % 7 + 1;

    auto& pair = SpriteDefines[id];

    Cell* cell = new AnimatedCell(pair.second, size);

    return cell;
}

void Cell::SetDebugInfo(int a, int b)
{
    return;
    removeAllChildrenWithCleanup(true);
    std::stringstream ss;
    ss << a << ":" << b;
    CCLabelTTF* l = CCLabelTTF::create();
    l->initWithString(ss.str().c_str(), "brookeshappelldots.ttf", 25);
    addChild(l);
    ccColor3B col;
    col.r = 1;
    col.g = 1;
    col.b = 0;
    l->setColor(col);
    l->setPosition(ccp(20, 20));
}

void Cell::setAdditionalOffset(const CCPoint& pt)
{
    CCNode::setPosition(m_originalPosition + pt);
}

void Cell::setPosition(const CCPoint& p)
{
    m_originalPosition = p;
}

const CCPoint& Cell::getOriginalPosition()
{
    return m_originalPosition;
}

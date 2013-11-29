#include "Precompiled.h"
#include "Cell.h"


// partile system test
#include "particle_nodes/CCParticleSystem.h"

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/

static CCTexture2D* tex = nullptr;

static const float SpriteW = 55.f;
static const float SpriteH = 60.f;
static const CCPoint MatrixDimension = CCPoint(SpriteW * CellField::MatrixLineSize, SpriteH * CellField::MatrixLineSize);

static std::pair<CCRect, Cell::Colour> SpriteDefines[] =
{
    std::make_pair(CCRectMake(1, 0, 55, 60), Cell::Red),
    std::make_pair(CCRectMake(58, 0, 55, 60), Cell::Brown),
    std::make_pair(CCRectMake(115, 0, 55, 60), Cell::Green),
    std::make_pair(CCRectMake(170, 0, 55, 60), Cell::Purple),
    std::make_pair(CCRectMake(225, 0, 55, 60), Cell::Aqua),

    std::make_pair(CCRectMake(0, 0, 0, 0), Cell::Undefined) //! Roadblock
};

CellField::CellField() :
m_lockedDirection(byNone),
m_state(MSIdle)
{
	m_ps = CCParticleSun::create();
	this->addChild(m_ps);
}

CellField::~CellField()
{

}

Cell* CellField::_createRandomCell()
{
    int id = rand() % 5;

    auto& pair = SpriteDefines[id];

    Cell* cell = new Cell(pair.second);

    if (!cell->initWithTexture(tex, pair.first))
    {
        assert("Wrong way" && false);
        return nullptr;
    }

    cell->setAnchorPoint(ccp(0, 0));

    return cell;
}

bool CellField::init()
{
    if (CCLayer::init())
    {
        if (!tex)
        {
            tex = new CCTexture2D();
            CCImage* image = new CCImage();
            image->initWithImageFile("spiders2.png");
            tex->initWithImage(image);
            image->release();
        }

        m_spriteDimentsion[byX] = SpriteW;
        m_spriteDimentsion[byY] = SpriteH;

        srand(static_cast<uint32_t>(time(nullptr)));

        m_movingCells[byX] = m_movingCells[byY] = nullptr;

        //! Build initial matrix
        //! Build a center matrix

        uint32_t a = 0;

        Cell* prevCell = nullptr;
        Cell* prevLine[MatrixLineSize]{nullptr};

        for (uint32_t i = 0; i < MatrixLineSize; ++i)
        {
            for (uint32_t j = 0; j < MatrixLineSize; ++j)
            {
                Cell* cell = _createRandomCell();

                assert(cell);

                addChild(cell);
                cell->setPosition(ccp(j * SpriteW, a));

                if (prevCell == nullptr)
                {
                    prevCell = cell;
                }
                else
                {
                    cell->prev = prevCell;
                    prevCell->next = cell;
                    prevCell = cell;
                }

                Cell*& upCell = prevLine[j];

                if (upCell == nullptr)
                {
                    upCell = cell;
                }
                else
                {
                    upCell->down = cell;
                    cell->up = upCell;
                    upCell = cell;
                }

                

                //! The first chunk will emplace at the left of the bubble matrix
                m_centerMatrix[i * MatrixLineSize + j] = ccp(cell->getPositionX() - MatrixLineSize * SpriteW,
                    cell->getPositionY());

                //! The second chunk will emplace at the origin of the bubble matrix
                m_centerMatrix[MatrixSize + (i * MatrixLineSize + j)] = cell->getPosition();

                //! The third chunk will emplace at the up of the bubble matrix
                m_centerMatrix[MatrixSize * 2 + (i * MatrixLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() + MatrixLineSize * SpriteH);

                //! The fourth chunk will emplace at the right of the bubble matrix
                m_centerMatrix[MatrixSize * 3 + (i * MatrixLineSize + j)] = ccp(cell->getPositionX() + MatrixLineSize * SpriteW,
                    cell->getPositionY());

                //! The fifth chunk will emplace at the bottom of the bubble matrix
                m_centerMatrix[MatrixSize * 4 + (i * MatrixLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() - MatrixLineSize * SpriteH);
            }

            prevCell = nullptr;

            a += static_cast<uint32_t>(SpriteH);
        }

        return true;
    }

    return false;
}


void CellField::_dragCells(const CCPoint& delta)
{
    Direction direction = m_lockedDirection;

    //! Lock the direction until a touch ends
    if (direction == byNone)
    {
        direction = std::abs(delta.x) > std::abs(delta.y) ? byX : byY;
        m_lockedDirection = direction;
    }

    if (_getState() == MSMoving)
    {
        Cell* baseCell = m_movingCells[m_lockedDirection];
        for (Cell* cell = baseCell; cell; cell = _next(cell, m_lockedDirection))
        {
            float d = _getPointFieldByDirection(cell->getPosition()) + _getPointFieldByDirection(delta);

            if (direction == byX)
            {
                cell->setPositionX(d);
            }
            else
            {
                cell->setPositionY(d);
            }
        }

        float fStepsCount = (_getPointFieldByDirection(baseCell->getPosition()) - _getPointFieldByDirection(m_from[m_lockedDirection])) / m_spriteDimentsion[m_lockedDirection];

        int iStepsCount = static_cast<int>(std::floor(fStepsCount + 0.5f));


        if (m_lockedDirection == byX)
        {
            if (iStepsCount == 1)
            {
                Cell* newCell = _createRandomCell();
                newCell->setPositionY(baseCell->getPositionY());
                newCell->setPositionX(baseCell->getPositionX() - SpriteW);
                addChild(newCell);

                newCell->next = baseCell;
                baseCell->prev = newCell;
                m_movingCells[m_lockedDirection] = newCell;
                newCell->dirty = true;
                //CCLog("N");
            }
            else if (iStepsCount == -1)
            {

            }
        }
    }

    m_lastDelta = delta;
}

void CellField::onTouchMoved(CCTouch* touch)
{
    CCPoint delta = touch->getDelta();

    _dragCells(delta);
}

void CellField::onTouchPressed(CCTouch* touch)
{

    m_lockedDirection = byNone;

    CCPoint to = touch->getLocation();

    CCPoint position = to - getPosition();

	m_ps->resetSystem();
	m_ps->setPosition(touch->getLocation());
	//m_ps->setSourcePosition(ccp(0,0));

    uint32_t i = 0;

    uint32_t cellCount = getChildrenCount();
    CCArray* children = getChildren();

    Cell* hitCell = nullptr;

    for (uint32_t i = 0; i < cellCount; ++i)
    {
        Cell* cell = static_cast<Cell*>(children->objectAtIndex(i));

        const CCPoint& cellPos = cell->getPosition();

        if (position.x >= cellPos.x && position.y >= cellPos.y && position.x <= (SpriteW + cellPos.x) && position.y <= (SpriteH + cellPos.y))
        {
            hitCell = cell;
            break;
        }
    }

    if (hitCell)
    {
        m_movingCells[byX] = _rewind(hitCell, byX, ToTheBegin);
        m_movingCells[byY] = _rewind(hitCell, byY, ToTheBegin);
        m_from[byX] = m_movingCells[byX]->getPosition();
        m_from[byY] = m_movingCells[byY]->getPosition();

        _advanceState(MSMoving);
    }
}

void CellField::onTouchReleased(CCTouch* touch)
{

    if (m_lockedDirection != byNone
        && (m_movingCells[byX] || m_movingCells[byY])
        )
    {
        _advanceState(MSStucking);
    }
    else
    {
        m_movingCells[byX] = m_movingCells[byY] = nullptr;
        _advanceState(MSIdle);
    }
}

Cell* CellField::_rewind(Cell* current, Direction dir, Rewind rew)
{
    if (dir == byX)
    {
        if (rew == ToTheEnd)
        {
            for (; current->next; current = current->next);
        }
        else
        {
            for (; current->prev; current = current->prev);
        }
    }
    else
    {
        if (rew == ToTheEnd)
        {
            for (; current->down; current = current->down);
        }
        else
        {
            for (; current->up; current = current->up);
        }
    }

    return current;
}

Cell* CellField::_advanceNode(Cell* node, int count) const
{
    if (count > 0)
    {
        for (int i = 0; i < count && node; node = node->next, ++i);
    }
    else if (count < 0)
    {
        for (int i = count; i < 0 && node; node = node->prev, ++i);
    }

    return node;
}

void CellField::_stabilizationState()
{
    if (m_stepsCount != 0)
    {
        if (m_lockedDirection == byX)
        {
            Cell* current = m_movingCells[m_lockedDirection];

            auto rebaseFunc = [this](Cell* curNode, int steps)
            {
                Cell* next = _advanceNode(curNode, steps);

                if (next && next->up)
                {
                    curNode->up = next->up;

                    curNode->up->down = curNode;
                }
                else
                {
                    curNode->up = nullptr;
                }

                if (next && next->down)
                {
                    curNode->down = next->down;
                    curNode->down->up = curNode;
                }
                else
                {
                    curNode->down = nullptr;
                }
            };

            if (m_stepsCount > 0)
            {
                for (; current; current = current->next)
                {
                    rebaseFunc(current, m_stepsCount);
                }
            }
            else
            {
                current = _rewind(current, byX, ToTheEnd);
                for (; current; current = current->prev)
                {
                    rebaseFunc(current, m_stepsCount);
                }
            }
        }
    }
}


void CellField::_stuckMovedCells()
{
    assert(m_lockedDirection != byNone);

    Cell* cell = m_movingCells[m_lockedDirection];

    CCPoint* point = &m_centerMatrix[0];

    const CCPoint& position = cell->getPosition();

    float diff =  _getPointFieldByDirection(position) - _getPointFieldByDirection(*point);

    for (uint32_t i = 1; i < CenterMatrixSize; i++)
    {
        CCPoint* curPoint = &m_centerMatrix[i];

        float curDiff = _getPointFieldByDirection(position) - _getPointFieldByDirection(*curPoint);

        if (std::abs(curDiff) < std::abs(diff))
        {
            diff = curDiff;
        }
    }

    for (; cell; cell = _next(cell, m_lockedDirection))
    {
        if (m_lockedDirection == byX)
        {
            cell->setPositionX(cell->getPositionX() - diff);
        }
        else
        {
            cell->setPositionY(cell->getPositionY() - diff);
        }
    }

    float fStepsCount = (_getPointFieldByDirection(position) - _getPointFieldByDirection(m_from[m_lockedDirection])) / m_spriteDimentsion[m_lockedDirection];

    m_stepsCount = static_cast<int>(std::floor(fStepsCount + 0.5f));
}

void CellField::_applyInertia(float value)
{

}

void CellField::onUpdate(float dt)
{
	m_ps->update(dt);

    if (_getState() == MSStucking)
    {
        _stuckMovedCells();

        _advanceState(MSStabilization);
    }
    else if (_getState() == MSStabilization)
    {
        _stabilizationState();

        _advanceState(MSIdle);
    }

//     if (m_inertiaInUse)
//     {
//         if (m_lockedDirection == byX && m_movingLine[0] != nullptr)
//         {
//             for (Cell *cell : m_movingLine)
//             {
//                 float x = cell->getPositionX();
// 
//                 x += m_lastDelta.x * m_inertia;
// 
//                 cell->setPositionX(x);
//             }
//         }
//         else
//         {
// 
//         }
// 
//         m_inertia -= dt;
//         m_inertia = std::max(0.f, m_inertia);
// 
//         if (m_inertia == 0.f)
//         {
//             m_inertiaInUse = false;
//             m_movingLine[0] = m_movingRow[0] = nullptr; //! fast invalidate
//             m_lockedDirection = byNone;
//         }
//     }
}

void CellField::_advanceState(MatrixState state)
{
    m_state = state;
}

CellField::MatrixState CellField::_getState() const
{
    return m_state;
}

Cell* CellField::_next(Cell* cur, Direction dir)
{
    assert(cur);

    if (dir == byX)
    {
        return cur->next;
    }
    else
    {
        return cur->down;
    }
}

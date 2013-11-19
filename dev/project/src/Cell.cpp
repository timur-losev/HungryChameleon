#include "Precompiled.h"
#include "Cell.h"


/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/

static CCTexture2D* tex = nullptr;

#define SpriteW 55
#define SpriteH 60

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

}

CellField::~CellField()
{

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

        memset(m_movingData[0], 0, MatrixLineSize * sizeof(Cell*));
        memset(m_movingData[1], 0, MatrixLineSize * sizeof(Cell*));

        //! Build initial matrix
        //! Build a center matrix

        uint32_t a = 0;

        Cell* prevCell = nullptr;
        Cell* prevLine[MatrixLineSize]{nullptr};

        for (uint32_t i = 0; i < MatrixLineSize; ++i)
        {
            for (uint32_t j = 0; j < MatrixLineSize; ++j)
            {
                int id = rand() % 5;

                auto& pair = SpriteDefines[id];

                Cell* cell = new Cell(pair.second);

                if (!cell->initWithTexture(tex, pair.first))
                {
                    assert("Wrong way" && false);
                    return false;
                }

                addChild(cell);

                cell->setPosition(ccp(j * 55, a));

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

                cell->setAnchorPoint(ccp(0, 0));
                m_centerMatrix[i * MatrixLineSize + j] = cell->getPosition();
            }

            prevCell = nullptr;

            a += 61;
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

        for (uint32_t i = 0; i < MatrixLineSize; ++i)
        {
            Cell* cell = m_movingData[m_lockedDirection][i];

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
        Cell* target = hitCell->next;

        Cell** movingLine = m_movingData[byX];
        Cell** movingRow = m_movingData[byY];

        movingLine[0] = hitCell;

        //! build cell moving line
        //! TODO:two-dir-cycle must be here
        uint32_t i = 1;
        for (; target; target = target->next, ++i)
        {
            assert(i < MatrixLineSize); //! omit checking this while the loop, but make a fuse
            movingLine[i] = target;
        }

        target = hitCell->prev;

        for (; target; target = target->prev, ++i)
        {
            assert(i < MatrixLineSize); //! omit checking this while the loop, but make a fuse
            movingLine[i] = target;
        }

        //! build cell moving row
        //! TODO:two-dir-cycle must be here
        movingRow[0] = hitCell;
        i = 1;

        target = hitCell->up;

        for (; target; target = target->up, ++i)
        {
            assert(i < MatrixLineSize); //! omit checking this while the loop, but make a fuse
            movingRow[i] = target;
        }

        target = hitCell->down;

        for (; target; target = target->down, ++i)
        {
            assert(i < MatrixLineSize); //! omit checking this while the loop, but make a fuse
            movingRow[i] = target;
        }

        m_from = hitCell->getPosition();

        _advanceState(MSMoving);
    }
}

void CellField::onTouchReleased(CCTouch* touch)
{
    if (m_lockedDirection != byNone
        && (m_movingData[byX][0] || m_movingData[byY][0])
        )
    {
        _advanceState(MSStucking);
    }
    else
    {
        _advanceState(MSIdle);
    }
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
            //if (m_stepsCount > 0)
            {
                Cell** cells = m_movingData[m_lockedDirection];

                //! Rebase line
                 for (uint32_t i = 0; i < MatrixLineSize; ++i)
                 {
                     Cell* curCell = cells[i];

                     if (m_stepsCount > 0)
                     {
                         if (curCell->up)
                         {
                             //curCell->up->down = _advanceNode(curCell->prev, -(m_stepsCount - 1));
                             curCell->up = _advanceNode(curCell->up->next, m_stepsCount - 1);
                         }
                         
                         if (curCell->down)
                         {
                             //curCell->down->up = _advanceNode(curCell->prev, -(m_stepsCount - 1));
                             curCell->down = _advanceNode(curCell->down->next, m_stepsCount - 1);
                         }
                     }
                     else if (m_stepsCount < 0)
                     {
                         if (curCell->up)
                         {
                             //curCell->up->down = _advanceNode(curCell->next, m_stepsCount - 1);
                             curCell->up = _advanceNode(curCell->up->prev, m_stepsCount + 1);
                         }
                         
                         if (curCell->down)
                         {
                             //curCell->down->up = _advanceNode(curCell->next, m_stepsCount - 1);
                             curCell->down = _advanceNode(curCell->down->prev, m_stepsCount + 1);
                         }
                     }
                 }

//                  Cell* curCell = cells[0];
// 
//                  if (m_stepsCount > 0)
//                  {
//                      curCell->up = _advanceNode(curCell->up->next, m_stepsCount - 1);
//                      curCell->down = _advanceNode(curCell->down->next, m_stepsCount - 1);
//                  }
//                  else if (m_stepsCount < 0)
//                  {
//                      curCell->up = _advanceNode(curCell->up->prev, m_stepsCount + 1);
//                      curCell->down = _advanceNode(curCell->down->prev, m_stepsCount + 1);
//                  }
            }
        }
        else
        {

        }
    }
}


void CellField::_stuckMovedCells()
{
    assert(m_lockedDirection != byNone);

    Cell* cell = *m_movingData[m_lockedDirection];

    CCPoint* point = &m_centerMatrix[0];

    const CCPoint& position = cell->getPosition();

    float diff =  _getPointFieldByDirection(position) - _getPointFieldByDirection(*point);

    for (uint32_t i = 1; i < MatrixSize; i++)
    {
        CCPoint* curPoint = &m_centerMatrix[i];

        float curDiff = _getPointFieldByDirection(position) - _getPointFieldByDirection(*curPoint);

        if (std::abs(curDiff) < std::abs(diff))
        {
            diff = curDiff;
        }
    }

    for (uint32_t i = 0; i < MatrixLineSize; ++i)
    {
        Cell* cell = m_movingData[m_lockedDirection][i];

        if (m_lockedDirection == byX)
        {
            cell->setPositionX(cell->getPositionX() - diff);
        }
        else
        {
            cell->setPositionY(cell->getPositionY() - diff);
        }
    }

    float fStepsCount = (_getPointFieldByDirection(position) - _getPointFieldByDirection(m_from)) / m_spriteDimentsion[m_lockedDirection];

    m_stepsCount = static_cast<int>(std::floor(fStepsCount + 0.5f));
}

void CellField::_applyInertia(float value)
{

}

void CellField::onUpdate(float dt)
{
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

#include "Precompiled.h"
#include "Cell.h"


/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
*/

static CCTexture2D* tex = nullptr;

static const float SpriteW = 55.f;
static const float SpriteH = 60.f;
static const CCPoint MatrixDimension = CCPoint(SpriteW * CellField::MatrixVisibleLineSize, SpriteH * CellField::MatrixVisibleLineSize);

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
m_state(MSIdle),
m_hitCell(nullptr)
{

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

        //! Build initial matrix
        //! Build a center matrix

        uint32_t a = 0;

        Cell* prevCell = nullptr;
        Cell* prevLine[MatrixVisibleLineSize]{nullptr};

        for (uint32_t i = 0; i < MatrixVisibleLineSize; ++i)
        {
            for (uint32_t j = 0; j < MatrixVisibleLineSize; ++j)
            {
                Cell* cell = _createRandomCell();

                assert(cell);

                addChild(cell);
                cell->setPosition(ccp(j * SpriteW, a));

                cell->rowId = i;
                cell->colId = j;

                m_rows[i].push_back(cell);
                m_cols[j].push_back(cell);

                //! The first chunk will emplace at the left of the bubble matrix
                m_centerMatrix[i * MatrixVisibleLineSize + j] = ccp(cell->getPositionX() - MatrixVisibleLineSize * SpriteW,
                    cell->getPositionY());

                //! The second chunk will emplace at the origin of the bubble matrix
                m_centerMatrix[MatrixSize + (i * MatrixVisibleLineSize + j)] = cell->getPosition();

                //! The third chunk will emplace at the up of the bubble matrix
                m_centerMatrix[MatrixSize * 2 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() + MatrixVisibleLineSize * SpriteH);

                //! The fourth chunk will emplace at the right of the bubble matrix
                m_centerMatrix[MatrixSize * 3 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX() + MatrixVisibleLineSize * SpriteW,
                    cell->getPositionY());

                //! The fifth chunk will emplace at the bottom of the bubble matrix
                m_centerMatrix[MatrixSize * 4 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() - MatrixVisibleLineSize * SpriteH);
            }

            a += static_cast<uint32_t>(SpriteH);
        }

        return true;
    }

    return false;
}

CellField::Line_t& CellField::_getLineByDirection(Cell* hitcell, Direction dir)
{
    if (dir == byX)
    {
        return m_rows[hitcell->rowId];
    }
    else
    {
        return m_cols[hitcell->colId];
    }
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
        //Cell* baseCell = m_movingCells[m_lockedDirection];
        //for (Cell* cell = baseCell; cell; cell = _next(cell, m_lockedDirection))

        Line_t& line = _getLineByDirection(m_hitCell, m_lockedDirection);

        for (Cell* cell : line)
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

        float fStepsCount = (_getPointFieldByDirection(m_hitCell->getPosition()) - _getPointFieldByDirection(m_from)) / m_spriteDimentsion[m_lockedDirection];

        m_stepsCount = static_cast<int>(std::floor(fStepsCount + 0.5f));

        if (m_lockedDirection == byX)
        {
            //if (iStepsCount == 1)
            {
                CCLog("%d %f", m_stepsCount, m_hitCell->getPositionX());
            }
            //else if (iStepsCount == -1)
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
        /*m_movingCells[byX] = _rewind(hitCell, byX, ToTheBegin);
        m_movingCells[byY] = _rewind(hitCell, byY, ToTheBegin);
        m_from[byX] = m_movingCells[byX]->getPosition();
        m_from[byY] = m_movingCells[byY]->getPosition();*/

        m_from = hitCell->getPosition();

        m_hitCell = hitCell;

        _advanceState(MSMoving);
    }
}

void CellField::onTouchReleased(CCTouch* touch)
{
    if (m_lockedDirection != byNone && m_hitCell)
    {
        _advanceState(MSStucking);
    }
    else
    {
        m_hitCell = nullptr;
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

    CCPoint* point = &m_centerMatrix[0];

    const CCPoint& position = m_hitCell->getPosition();

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

    Line_t& line = _getLineByDirection(m_hitCell, m_lockedDirection);

    for (Cell* cell : line)
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

    float fStepsCount = (_getPointFieldByDirection(position) - _getPointFieldByDirection(m_from)) / m_spriteDimentsion[m_lockedDirection];

    int iSc = static_cast<int>(std::floor(fStepsCount + 0.5f));

    assert(iSc == m_stepsCount);
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
        //_stabilizationState();

        _advanceState(MSIdle);
    }
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

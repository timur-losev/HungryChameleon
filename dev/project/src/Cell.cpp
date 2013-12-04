#include "Precompiled.h"
#include "Cell.h"
#include "AnimatedCell.h"

// particle system test
#include "particle_nodes/CCParticleSystem.h"

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

Cell::Cell(Colour c)
: color(c)
{
	auto& pair = SpriteDefines[c];

	CCSprite* a = CCSprite::create();
	if (!a->initWithTexture(tex, pair.first))
	{
		assert("Wrong way" && false);
	}

	a->setAnchorPoint(ccp(0, 0));
	addChild(a);
}

CellField::CellField() :
m_lockedDirection(byNone),
m_state(MSIdle),
m_hitCell(nullptr),
m_prevStep(0)
{

}

CellField::~CellField()
{

}

Cell* CellField::_createRandomCell()
{
    int id = rand() % 4;

    auto& pair = SpriteDefines[id];

	Cell* cell = new AnimatedCell(pair.second);

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
        Line_t& line = _getLineByDirection(m_hitCell, m_lockedDirection);

        if (m_hitCell->markedForRemove)
        {
            Cell* next = _next(m_hitCell, m_lockedDirection, line);
            _removeCell(m_hitCell);
            m_hitCell = next;
            m_prevStep = 0;
            _advanceState(MSStucking);
            return;
        }

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

        _stabilizeMatrix(line);
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
    if (_getState() != MSIdle)
    {
        return;
    }

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
        m_from = hitCell->getPosition();

        m_hitCell = hitCell;

        _advanceState(MSMoving);


		_onCellRemoved(hitCell);
    }
}

void CellField::onTouchReleased(CCTouch* touch)
{
    if (m_lockedDirection != byNone && m_hitCell)
    {
        m_prevStep = 0;
        _advanceState(MSStucking);
    }
    else
    {
        m_hitCell = nullptr;
        _advanceState(MSIdle);
    }
}

void CellField::_stuckMovedCells()
{
    assert(m_lockedDirection != byNone);

    CCPoint* point = &m_centerMatrix[0];

    const CCPoint& position = m_hitCell->getPosition();

    float diff = _getPointFieldByDirection(position) - _getPointFieldByDirection(*point);

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

}

void CellField::onUpdate(float dt)
{
    if (_getState() == MSStucking)
    {
        _stuckMovedCells();

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

Cell* CellField::_next(Cell* cur, Direction dir, const Line_t& line)
{
    assert(cur);

    if (dir == byX)
    {
        if (cur->colId < (int)line.size() - 1)
        {
            return line[cur->colId + 1];
        }
        else
        {
            return line[cur->colId - 1];
        }
    }
    else
    {
        if (cur->rowId < (int)line.size() - 1)
        {
            return line[cur->rowId + 1];
        }
        else
        {
            return line[cur->rowId - 1];
        }
    }

    return nullptr;
}

void CellField::_stabilizeMatrix(Line_t &line)
{
    int delta = m_stepsCount - m_prevStep;

    if (m_lockedDirection == byX)
    {
        if (delta == 1)
        {
            m_prevStep = m_stepsCount;

            Cell* zeroCell = line.front();
            Cell* newCell = _createRandomCell();
            newCell->setPositionY(zeroCell->getPositionY());
            newCell->setPositionX(zeroCell->getPositionX() - SpriteW);
            addChild(newCell);

            line.push_front(newCell);
            Cell* toRemove = line.back();
            line.pop_back();

            _rebaseByX(zeroCell, line);

            _removeCellIfPossible(toRemove);
        }
        else if (delta == -1)
        {
            m_prevStep = m_stepsCount;

            Cell* zeroCell = line.back();
            Cell* newCell = _createRandomCell();
            newCell->setPositionY(zeroCell->getPositionY());
            newCell->setPositionX(zeroCell->getPositionX() + SpriteW);
            addChild(newCell);

            line.push_back(newCell);
            Cell* toRemove = line.front();
            line.pop_front();

            _rebaseByX(zeroCell, line);

            _removeCellIfPossible(toRemove);
        }
    }
    else
    {
        if (delta == 1)
        {
            m_prevStep = m_stepsCount;

            Cell* zeroCell = line.front();
            Cell* newCell = _createRandomCell();

            newCell->setPositionY(zeroCell->getPositionY() - SpriteH);
            newCell->setPositionX(zeroCell->getPositionX());

            addChild(newCell);

            line.push_front(newCell);
            Cell* toRemove = line.back();
            line.pop_back();

            _rebaseByY(zeroCell, line);

            _removeCellIfPossible(toRemove);
        }
        else if (delta == -1)
        {
            m_prevStep = m_stepsCount;

            Cell* zeroCell = line.back();
            Cell* newCell = _createRandomCell();

            newCell->setPositionY(zeroCell->getPositionY() + SpriteH);
            newCell->setPositionX(zeroCell->getPositionX());

            addChild(newCell);

            line.push_back(newCell);
            Cell* toRemove = line.front();
            line.pop_front();

            _rebaseByY(zeroCell, line);

            _removeCellIfPossible(toRemove);
        }
    }
}

void CellField::_rebaseByX(Cell* sampleCell, Line_t& row)
{
    uint32_t j = 0;
    for (size_t i = 0; i < MatrixVisibleLineSize; ++i)
    {
        Line_t& col = m_cols[i];

        Cell* exchangeCell = row[j];

        exchangeCell->rowId = sampleCell->rowId;
        exchangeCell->colId = i;

        col[sampleCell->rowId] = exchangeCell;

        ++j;
    }
}

void CellField::_rebaseByY(Cell* sampleCell, Line_t& col)
{
    uint32_t j = 0;
    for (size_t i = 0; i < MatrixVisibleLineSize; ++i)
    {
        Line_t& row = m_rows[i];

        Cell* exchangeCell = col[j];

        exchangeCell->colId = sampleCell->colId;
        exchangeCell->rowId = i;

        row[sampleCell->colId] = exchangeCell;

        ++j;
    }
}

void CellField::_removeCell(Cell* cell)
{
    removeChild(static_cast<CCNode*>(cell), true);
    cell->release();
}

void CellField::_removeCellIfPossible(Cell* cell)
{
    if (m_hitCell != cell)
    {
        _removeCell(cell);
    }
    else if (m_hitCell)
    {
        m_hitCell->markedForRemove = true;
    }
}

void CellField::_onCellRemoved(Cell* cell)
{
#if 0
	CCParticleSystem* ps = CCParticleExplosion::createWithTotalParticles(100);
	ps->autorelease();
	ps->setPosition(cell->convertToNodeSpace(cell->getPosition()));
	cell->addChild(ps);
#endif // 0

}

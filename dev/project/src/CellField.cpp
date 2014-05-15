#include "Precompiled.h"
#include "CellField.h"
#include "AnimatedCell.h"
#include "Cell.h"

#include "MatrixStateMoving.h"
#include "MatrixStateMatching.h"
#include "MatrixStateRemove.h"
#include "MatrixStateFill.h"

// particle system test
#include "particle_nodes/CCParticleSystem.h"

/*
    ###################CONCEPT#########################
    DO NOT PULL INTO PRODUCTION
    */

//extern CCTexture2D* tex;

//static const float m_cellWidth = 55.f;
//static const float m_cellHeight = 60.f;
//static const CCPoint MatrixDimension = CCPoint(m_cellWidth * CellField::MatrixVisibleLineSize, m_cellHeight * CellField::MatrixVisibleLineSize);

CellField::CellField() :
m_lockedDirection(byNone),
m_state(MSIdle),
m_hitCell(nullptr),
m_prevStep(0),
m_cellWidth(55.f),
m_cellHeight(60.f)
{
    //pushState(new MatrixStateFill);
}

CellField::~CellField()
{

}

bool CellField::init(float cellWidth, float cellHeight)
{
    scheduleUpdate();
    m_cellHeight = cellHeight;
    m_cellWidth = cellWidth;

    if (CCLayer::init())
    {
        m_spriteDimentsion[byX] = m_cellWidth;
        m_spriteDimentsion[byY] = m_cellHeight;

        srand(static_cast<uint32_t>(time(nullptr)));

        //! Build initial matrix
        //! Build a center matrix

        uint32_t a = 0;

        for (uint32_t i = 0; i < MatrixVisibleLineSize; ++i)
        {
            for (uint32_t j = 0; j < MatrixVisibleLineSize; ++j)
            {
                Cell* cell = _randomCell();

                assert(cell);

                addChild(cell);
                cell->setPosition(ccp(j * m_cellWidth, a));

                cell->rowId = i;
                cell->colId = j;

                cell->setDebugInfo(cell->rowId, cell->colId);

                m_rows[i].push_back(cell);
                m_cols[j].push_back(cell);

                //! The first chunk will emplace at the left of the bubble matrix
                m_centerMatrix[i * MatrixVisibleLineSize + j] = ccp(cell->getPositionX() - MatrixVisibleLineSize * m_cellWidth,
                    cell->getPositionY());

                //! The second chunk will emplace at the origin of the bubble matrix
                m_centerMatrix[MatrixSize + (i * MatrixVisibleLineSize + j)] = cell->getPosition();

                //! The third chunk will emplace at the up of the bubble matrix
                m_centerMatrix[MatrixSize * 2 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() + MatrixVisibleLineSize * m_cellHeight);

                //! The fourth chunk will emplace at the right of the bubble matrix
                m_centerMatrix[MatrixSize * 3 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX() + MatrixVisibleLineSize * m_cellWidth,
                    cell->getPositionY());

                //! The fifth chunk will emplace at the bottom of the bubble matrix
                m_centerMatrix[MatrixSize * 4 + (i * MatrixVisibleLineSize + j)] = ccp(cell->getPositionX(),
                    cell->getPositionY() - MatrixVisibleLineSize * m_cellHeight);
            }

            a += static_cast<uint32_t>(m_cellHeight);
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
        direction = abs(delta.x) > abs(delta.y) ? byX : byY;
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

        m_stepsCount = static_cast<int>(floor(fStepsCount + 0.5f));

        _stabilizeMatrix(line);
    }

    m_lastDelta = delta;
}

void CellField::ccTouchMoved(CCTouch *touch, CCEvent *pEvent)
{
    CCPoint delta = touch->getDelta();

    _dragCells(delta);
}

bool CellField::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
    if (_getState() != MSIdle)
    {
        return true;
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

        if (position.x >= cellPos.x && position.y >= cellPos.y && position.x <= (m_cellWidth + cellPos.x) && position.y <= (m_cellHeight + cellPos.y))
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

    }
    return true;
}

void CellField::ccTouchEnded(CCTouch *touch, CCEvent *pEvent)
{
    if (m_lockedDirection != byNone && m_hitCell)
    {
        m_prevStep = 0;
        _advanceState(MSStucking);
    }
    else
    {
        _advanceState(MSIdle);
        m_hitCell = nullptr;
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

        if (abs(curDiff) < abs(diff))
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

void CellField::update(float dt)
{
    if (_getState() == MSStucking)
    {
        _stuckMovedCells();

        _advanceState(MSMatching);
    }
    else if (_getState() == MSMatching)
    {
        _matchingState();
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
            Cell* newCell = _randomCell();
            newCell->setPositionY(zeroCell->getPositionY());
            newCell->setPositionX(zeroCell->getPositionX() - m_cellWidth);
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
            Cell* newCell = _randomCell();
            newCell->setPositionY(zeroCell->getPositionY());
            newCell->setPositionX(zeroCell->getPositionX() + m_cellWidth);
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
            Cell* newCell = _randomCell();

            newCell->setPositionY(zeroCell->getPositionY() - m_cellHeight);
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
            Cell* newCell = _randomCell();

            newCell->setPositionY(zeroCell->getPositionY() + m_cellHeight);
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

void CellField::_floodFill(Cell* cell, Cell::Colour targetColour, std::list<Cell*>& matchingList) const
{
    if (cell->colour != targetColour || cell->travelsed)
    {
        return;
    }
    cell->travelsed = true;

    matchingList.push_back(cell);

    if (cell->colId > 0)
        _floodFill(m_cols[cell->colId - 1][cell->rowId], targetColour, matchingList); //! West

    if (cell->colId < MatrixVisibleLineSize - 1)
        _floodFill(m_cols[cell->colId + 1][cell->rowId], targetColour, matchingList); //! East

    if (cell->rowId < MatrixVisibleLineSize - 1)
        _floodFill(m_rows[cell->rowId + 1][cell->colId], targetColour, matchingList); //! North

    if (cell->rowId > 0)
        _floodFill(m_rows[cell->rowId - 1][cell->colId], targetColour, matchingList); //! South
}

void CellField::_matchingState()
{
    std::list<CellList_t> matchings;

    for (Line_t& line : m_rows)
    {
        for (Cell* cell : line)
        {

            cell->setDebugInfo(cell->rowId, cell->colId);
            std::list<Cell*> matchingList;

            if (!cell)
                continue;
            _floodFill(cell, cell->colour, matchingList);

            if (matchingList.size() >= 3)
            {
                matchings.push_back(matchingList);
            }
        }
    }

    _fallDownState(matchings);
}

void CellField::_fallDownState(const std::list<CellList_t>& matchedCells)
{
    //! Clean up
    for (const CellList_t& clist : matchedCells)
    {
        for (Cell* cell : clist)
        {
            m_rows[cell->rowId][cell->colId] = nullptr;
            m_cols[cell->colId][cell->rowId] = nullptr;

            _removeCell(cell);
        }
    }
    return;
    // Fill
    for (uint32_t i = 0; i < MatrixVisibleLineSize; ++i)
    {
        for (uint32_t j = 0; j < MatrixVisibleLineSize; ++j)
        {
            Cell* cell = m_cols[i][j];
            if (cell == nullptr)
            {
                _moveColumnFragmenDown(i, j, 1);
            }
        }
    }

}

void CellField::_moveColumnFragmenDown(uint32_t columnIndex, uint32_t startingFromRow, uint32_t numberOfPositions)
{
    int toPosition = startingFromRow;

    for (int i = startingFromRow; i < MatrixVisibleLineSize; ++i)
    {
        toPosition = i;
        if (m_cols[columnIndex][i])
        {
            break;
        }
    }
    if (!m_cols[columnIndex][toPosition] && toPosition == MatrixVisibleLineSize - 1)
    {
        toPosition = MatrixVisibleLineSize;
    }

    Line_t fromLine = m_cols[columnIndex];
    uint32_t newInd = toPosition;
    uint32_t oldInd = startingFromRow;

    CCPoint pos = ccp(columnIndex * m_cellWidth, 0);
    for (; oldInd < MatrixVisibleLineSize && newInd < MatrixVisibleLineSize; ++oldInd, ++newInd)
    {
        Cell* cell = fromLine[oldInd];
        m_cols[columnIndex][newInd] = cell;
        m_rows[newInd][columnIndex] = cell;
        if (cell)
        {
            cell->setPosition(pos);
            cell->rowId = newInd;
        }
        pos.y += static_cast<uint32_t>(m_cellHeight);
    }

    return;
    for (; newInd < MatrixVisibleLineSize; ++newInd)
    {
        Cell* cell = _randomCell();

        assert(cell);

        addChild(cell);
        cell->setPosition(pos);

        cell->rowId = newInd;
        cell->colId = columnIndex;
        m_rows[cell->rowId][cell->colId] = cell;
        m_cols[cell->colId][cell->rowId] = cell;

        pos.y += static_cast<uint32_t>(m_cellHeight);
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
#if 1
    CCParticleSystem* ps = CCParticleExplosion::createWithTotalParticles(100);
    ps->autorelease();
    ps->setPosition(cell->convertToNodeSpace(cell->getPosition()));
    cell->addChild(ps);
#endif // 0

}

Cell* CellField::_randomCell()
{
    return Cell::createRandom(ccp(m_cellWidth, m_cellHeight));
}


IMatrixState* CellField::_popState()
{
    if (m_stateQueue.empty())
    {
        return nullptr;
    }
    IMatrixState* result = m_stateQueue.front();
    m_stateQueue.pop();
    return result;
}

void CellField::pushState(IMatrixState* state)
{
    m_stateQueue.push(state);
}

#pragma once

#include "MatrixStateType.h"
#include "MatrixControllerEvents.h"

class CellContainer;
class IMatrixState;

class MatrixController : public CCLayer
{
public:
    typedef std::vector<CellContainer*> Line_t;
    typedef std::vector<Line_t> Matrix_t;

    MatrixControllerEvents::OnTouchBegan_t m_onTouchBegan;
    MatrixControllerEvents::OnTouchMoved_t m_onTouchMoved;
    MatrixControllerEvents::OnTouchEnded_t m_onTouchEnded;

private:
    uint32_t                    m_additionalWidth = 0;
    uint32_t                    m_additionalHeight = 0;
    uint32_t                    m_visibleWidth = 5;
    uint32_t                    m_visibleHeight = 5;

    typedef std::vector<IMatrixState*> MatrixStates_t;

    MatrixStates_t                  m_matrixStates;

    std::queue<IMatrixState*>   m_stateQueue;
    IMatrixState*               m_currentState = nullptr;

    Matrix_t                    m_matrix;

    CCSize                      m_cellSize;

private:
    void                       _advanceState();
    void                       _changeState(IMatrixState*);
public:
    MatrixController();
    ~MatrixController();
    
    void                        update(float);

    const IMatrixState*         getState(MatrixStateType::Enum) const;
    IMatrixState*               getState(MatrixStateType::Enum);

    bool                        init(float cellWidth, float cellHeight);

    const CCSize&               getCellSize() const;

    CellContainer*              getCellAtTouchPoint(const CCPoint& touchLocation) const;

    bool                        ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void                        ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void                        ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    Matrix_t&                   getMatrix();

    uint32_t                    additionalWidth() const { return m_additionalWidth; }
    uint32_t                    additionalHeight() const { return m_additionalHeight; }
    uint32_t                    visibleWidth() const { return m_visibleWidth; }
    uint32_t                    visibleHeight() const { return m_visibleHeight; }
    uint32_t                    totalWidth() const { return m_visibleWidth; }
    uint32_t                    totalHeight() const { return m_visibleHeight; }

};

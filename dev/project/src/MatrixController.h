#pragma once

class IMatrixState;
class CellContainer;

class MatrixController : public CCLayer
{
public:
    typedef std::vector<CellContainer*> Line_t;
    typedef std::vector<Line_t> Matrix_t;

    signal2<CCTouch*, CCEvent*> TouchBegan;
    signal2<CCTouch*, CCEvent*> TouchEnded;
    signal2<CCTouch*, CCEvent*> TouchMoved;
public:
    MatrixController();
    ~MatrixController();
    
    void                        pushState(IMatrixState*);
    void                        update(float);

    bool                        init(float cellWidth, float cellHeight);
    float                       getCellWidth() const;
    float                       getCellHeight() const;

    bool                        ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void                        ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void                        ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    Matrix_t&                   getMatrix();

    uint32_t                    additionalWidth() { return m_additionalWidth; }
    uint32_t                    additionalHeight() { return m_additionalHeight; }
    uint32_t                    visibleWidth() { return m_visibleWidth; }
    uint32_t                    visibleHeight() { return m_visibleHeight; }
    uint32_t                    totalWidth() { return m_visibleWidth + m_additionalWidth * 2; }
    uint32_t                    totalHeight() { return m_visibleHeight + m_additionalHeight * 2; }

private:
    void                       _popState();

private:
    uint32_t                    m_additionalWidth = 5;
    uint32_t                    m_additionalHeight = 5;
    uint32_t                    m_visibleWidth = 5;
    uint32_t                    m_visibleHeight = 5;

    std::queue<IMatrixState*>   m_stateQueue;
    IMatrixState*               m_currentState = nullptr;

    Matrix_t                    m_matrix;

    float                       m_cellWidth;
    float                       m_cellHeight;

	//typedef std::list<CellContainer*> CellList_t;
	//typedef std::deque<CellContainer*> Line_t;
	//Line_t						m_rows[MatrixVisibleLineSize];
	//Line_t						m_cols[MatrixVisibleLineSize];
};

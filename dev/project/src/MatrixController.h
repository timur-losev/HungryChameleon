#pragma once

class IMatrixState;
class CellContainer;

class MatrixController : public CCLayer
{
public:
	static const uint32_t MatrixVisibleLineSize = 6;
	//static const uint32_t MatrixSize = MatrixVisibleLineSize * MatrixVisibleLineSize;
	//static const uint32_t CenterMatrixSize = MatrixSize * 5;

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

    bool		                ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void		                ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void		                ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

    Matrix_t&                   getMatrix();

private:
	void                       _popState();

private:
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

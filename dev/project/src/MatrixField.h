#pragma once

class MatrixField
{
private:
    int**                   m_Field;
public:
    typedef std::vector<CCPoint> MatchesList_t;

    enum ESpecialBubbles
    {
        eEmptyCell = -1,
        eWaitAnim = -2
    };

    enum 
    {
        k_MaxFieldSize = 100,
        k_MaxVisibleSize = 10,
        k_MaxTypesCount = 6
    };

    MatrixField();
    virtual ~MatrixField();

    void                generateField(bool isRegenerate = false);
    void                scroll(int direction, uint32_t startX, uint32_t startY);
    void                scrollDown();
    inline int          getVisible(uint32_t x, uint32_t y) 
    {
        if (x < k_MaxVisibleSize && y < k_MaxVisibleSize)
        {
            return m_Field[y][x];
        }

        return eEmptyCell;
    }

    MatchesList_t getFirstMatches();
};
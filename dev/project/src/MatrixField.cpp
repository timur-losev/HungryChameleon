#include "Precompiled.h"
#include "MatrixField.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

MatrixField::MatrixField()
{
    srand(static_cast<uint32_t>(time(NULL)));

    m_Field = new int*[k_MaxFieldSize];
    for (int i = 0; i < k_MaxFieldSize; ++i)
    {
        m_Field[i] = new int[k_MaxFieldSize];
        memset(m_Field[i], eEmptyCell, k_MaxFieldSize * sizeof(int));
    }
}

MatrixField::~MatrixField()
{
    for (uint32_t i = 0; i < k_MaxFieldSize; ++i)
    {
        delete m_Field[i];
    }

    delete[] m_Field;
}

void MatrixField::generateField(bool isRegenerate)
{
    for (uint32_t i = 0; i < k_MaxFieldSize; ++i)
    {
        for (uint32_t j = 0; j < k_MaxFieldSize; ++j)
        {
            int prevx = (j > 0) ? m_Field[i][j - 1] : -1;
            int prevy = (i > 0) ? m_Field[i - 1][j] : -1;
            int newValue = eEmptyCell;

            assert(k_MaxTypesCount > 1);

            do
            {
                newValue = rand() % k_MaxTypesCount;
            }
            while(newValue == prevx || newValue == prevy);

            if (!isRegenerate || m_Field[i][j] == eEmptyCell)
            {
                m_Field[i][j] = newValue;
            }
        }
    }
}

void MatrixField::scroll(int direction, uint32_t startX, uint32_t startY)
{
    // direction
    // -1 - left
    // -2 - right
    // 0 - top
    // 1 - down

    if (k_MaxFieldSize <= startX || k_MaxFieldSize <= startY)
    {
        return;
    }

    int startIndex      = (-1 == direction || 0 == direction) ? 0 : k_MaxFieldSize - 1;
    int endIndex        = (-1 == direction || 0 == direction) ? k_MaxFieldSize - 1 : 0;
    int directionSign   = (-1 == direction || 0 == direction) ? 1 : -1;

    // Store first element
    int temp = (direction >= 0) ? m_Field[startIndex][startY] : m_Field[startX][startIndex];

    // Shift all items 
    for (int i = 0; i < k_MaxFieldSize - 1; i++)
    {
        int pos = abs(startIndex - i);
        if (direction >= 0)
        {
            m_Field[pos][startY] = m_Field[pos + directionSign][startY];
        }
        else
        {
            m_Field[startX][pos] = m_Field[startX][pos + directionSign];
        }
    }

    // restore first element in end of list
    if (direction >= 0)
    {
        m_Field[endIndex][startY] = temp;
    }
    else
    {
        m_Field[startX][endIndex] = temp;
    }
}

void MatrixField::scrollDown()
{
    // Horizontal
    for (uint32_t row = 0; row < k_MaxVisibleSize; row++)
    {
        for (uint32_t col = 0; col < k_MaxVisibleSize; ++col)
        {
            // if 3 color matches
            if (m_Field[row][col] == eWaitAnim)
            {
                for (int m = row; m > 0; --m)
                {
                    m_Field[m][col] = m_Field[m - 1][col];
                }
                m_Field[0][col] = rand() % k_MaxTypesCount;

                row = 0;
            }
        }
    }

    // Vertical
    for (uint32_t row = 0; row < k_MaxVisibleSize; row++)
    {
        for (uint32_t col = 0; col < k_MaxVisibleSize; ++col)
        {
            if (m_Field[row][col] == eWaitAnim)
            {
                int beg = row;
                int currColor = m_Field[row][col];
                // copy indexes of all matches colors
                while(beg < k_MaxVisibleSize &&
                    currColor == m_Field[beg][col])
                {
                    ++beg;
                }

                // scroll down 
                size_t lineSize = beg - row;
                for (size_t m = row + lineSize - 1; m > 0; --m)
                {
                    if (m >= lineSize)
                    {
                        m_Field[m][col] = m_Field[m - lineSize][col];
                    }
                    else
                    {
                        m_Field[m][col] = rand() % k_MaxTypesCount;
                    }
                }
                row = 0;
            }
        }
    }
}

MatrixField::MatchesList_t MatrixField::getFirstMatches()
{
    MatrixField::MatchesList_t matches;
    bool found = false;
    // Horizontal
    for (uint32_t row = 0; row < k_MaxVisibleSize; row++)
    {
        for (uint32_t col = 0; col < k_MaxVisibleSize - 2; ++col)
        {
            // if 3 color matches
            if (m_Field[row][col] >= 0 && m_Field[row][col] == m_Field[row][col + 1] && m_Field[row][col] == m_Field[row][col + 2])
            {
                int beg = col;
                int currColor = m_Field[row][col];
                // copy indexes of all matches colors
                while(beg < k_MaxVisibleSize &&
                    currColor == m_Field[row][beg])
                {
                    matches.push_back(CCPointMake(row, beg));
                    m_Field[row][beg] = eWaitAnim;
                    ++beg;
                }

                return matches;
            }
        }
    }

    // Vertical
    for (uint32_t row = 0; row < k_MaxVisibleSize - 2; row++)
    {
        for (uint32_t col = 0; col < k_MaxVisibleSize; ++col)
        {
            if (m_Field[row][col] >= 0 && m_Field[row][col] == m_Field[row + 1][col] && m_Field[row][col] == m_Field[row + 2][col])
            {
                int beg = row;
                int currColor = m_Field[row][col];
                // copy indexes of all matches colors
                while(beg < k_MaxVisibleSize &&
                    currColor == m_Field[beg][col])
                {
                    matches.push_back(CCPointMake(beg, col));
                    m_Field[beg][col] = eWaitAnim;
                    ++beg;
                }

                return matches;
            }
        }
    }

    return matches;
}


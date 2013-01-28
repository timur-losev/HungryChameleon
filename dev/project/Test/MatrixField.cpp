#include "MatrixField.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int MatrixField::m_MaxFieldSize		= 100;
int MatrixField::m_MaxVisibleSize	= 10;
int MatrixField::m_MaxTypesCount	= 4;

MatrixField::MatrixField()
{
	srand(time(NULL));

	m_Field = new int*[m_MaxFieldSize];
	for (int i = 0; i < m_MaxFieldSize; ++i)
	{
		m_Field[i] = new int[m_MaxFieldSize];
		memset(m_Field[i], -1, m_MaxFieldSize * sizeof(int));
	}
}

MatrixField::~MatrixField()
{
	for (int i = 0; i < m_MaxFieldSize; ++i)
	{
		delete[] m_Field[i];
	}
	delete[] m_Field;
}

void MatrixField::GenerateField(bool isRegenerate)
{
	for (int i = 0; i < m_MaxFieldSize; ++i)
	{
		for (int j = 0; j < m_MaxFieldSize; ++j)
		{
			int prevx = (j > 0) ? m_Field[i][j - 1] : -1;
			int prevy = (i > 0) ? m_Field[i - 1][j] : -1;
			int newValue = -1;

			assert(m_MaxTypesCount > 1);

			do
			{
				newValue = rand() % m_MaxTypesCount;
			}
			while(newValue == prevx || newValue == prevy);

			if (!isRegenerate || m_Field[i][j] == -1)
			{
				m_Field[i][j] = newValue;
			}
		}
	}
}

void MatrixField::Scroll(int direction, int startX, int startY)
{
	// direction
	// -1 - left
	// -2 - right
	// 0 - top
	// 1 - down

	if (0 > startX || 0 > startY ||
		m_MaxFieldSize <= startX || m_MaxFieldSize <= startY)
	{
		return;
	}

	int startIndex		= (-1 == direction || 0 == direction) ? 0 : m_MaxFieldSize - 1;
	int endIndex		= (-1 == direction || 0 == direction) ? m_MaxFieldSize - 1 : 0;
	int directionSign	= (-1 == direction || 0 == direction) ? 1 : -1;

	// Store first element
	int temp = (direction >= 0) ? m_Field[startIndex][startY] : m_Field[startX][startIndex];

	// Shift all items 
	for (int i = 0; i < m_MaxFieldSize - 1; i++)
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

	// resore first element in end of list
	if (direction >= 0)
	{		
		m_Field[endIndex][startY] = temp;
	}
	else
	{
		m_Field[startX][endIndex] = temp;
	}
}

MatchesList_t MatrixField::GetFirstMatches()
{
	MatchesList_t matches;
	bool found = false;
	// Horizontal
	for (int row = 0; row < m_MaxVisibleSize; row++)
	{
		for (int col = 0; col < m_MaxVisibleSize - 2; ++col)
		{
			// if 3 color matches
			if (m_Field[row][col] == m_Field[row][col + 1] && m_Field[row][col] == m_Field[row][col + 2])
			{
				int beg = col;
				int currColor = m_Field[row][col];
				// copy indexes of all matches colors
				while(beg < m_MaxVisibleSize &&
					  currColor == m_Field[row][beg])
				{
					matches.push_back(CCPointMake(row, beg));
					//m_Field[row][beg] = -1;
					++beg;
				}
				// scroll down 
				size_t lineSize = matches.size();
				for (beg = col; beg < col + lineSize; ++beg)
				{
					for (int m = row; m > 0; --m)
					{
						m_Field[m][beg] = m_Field[m - 1][beg];
					}
					m_Field[0][beg] = rand() % m_MaxTypesCount;
				}
				
				return matches;
			}
		}
	}

	// Vertical
	for (int row = 0; row < m_MaxVisibleSize - 2; row++)
	{
		for (int col = 0; col < m_MaxVisibleSize; ++col)
		{
			if (m_Field[row][col] == m_Field[row + 1][col] && m_Field[row][col] == m_Field[row + 2][col])
			{
				int beg = row;
				int currColor = m_Field[row][col];
				// copy indexes of all matches colors
				while(beg < m_MaxVisibleSize &&
					  currColor == m_Field[beg][col])
				{
					matches.push_back(CCPointMake(beg, col));
					m_Field[beg][col] = rand() % m_MaxTypesCount;
					++beg;
				}

				// scroll down 
				size_t lineSize = matches.size();
				for (int m = row + lineSize - 1; m > 0; --m)
				{
					if (m >= lineSize)
					{
						m_Field[m][col] = m_Field[m - lineSize][col];
					}
					else
					{
						m_Field[m][col] = rand() % m_MaxTypesCount;
					}					
				}
								
				return matches;
			}
		}
	}

	return matches;
}


#include "MatrixField.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

MatrixField::MatrixField()
{
	srand(time(NULL));

	for (int i = 0; i < m_MaxFieldSize; ++i)
	{
		memset(m_Field[i], -1, m_MaxFieldSize * sizeof(int));
	}
}

MatrixField::~MatrixField()
{

}

void MatrixField::GenerateField()
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

			m_Field[i][j] = newValue;
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

	int startIndex = (-1 == direction || 0 == direction) ? 0 : m_MaxFieldSize - 1;
	int endIndex = (-1 == direction || 0 == direction) ? m_MaxFieldSize - 1 : 0;
	int directionSign = (-1 == direction || 0 == direction) ? 1 : -1;

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
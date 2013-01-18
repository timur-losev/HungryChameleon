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
}
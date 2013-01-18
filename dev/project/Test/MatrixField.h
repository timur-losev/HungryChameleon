#pragma once
#include <assert.h>

class MatrixField
{
private:
	static const int	m_MaxFieldSize = 100;
	static const int	m_MaxVisibleSize = 10;
	static const int	m_MaxTypesCount = 3;
	int					m_Field[m_MaxFieldSize][m_MaxFieldSize];
protected:
public:
    MatrixField();
    virtual ~MatrixField();

	void				GenerateField();
	void				Scroll(int direction, int startX, int startY);
	inline int			GetVisible(int x, int y) 
	{
		if (x >= 0 || x < m_MaxVisibleSize || y >= 0 || y < m_MaxVisibleSize)
		{
			return m_Field[y][x];
		}

		return -1;
	}
	static const int	GetMaxFieldSize() { return m_MaxFieldSize; }
	static const int	GetMaxVisible() { return m_MaxVisibleSize; }
	static const int	GetMaxTypes() { return m_MaxTypesCount; }
};
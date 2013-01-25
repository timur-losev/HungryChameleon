#pragma once
#include <assert.h>
#include <vector>
#include <cocos2d.h>
using namespace cocos2d;

typedef std::vector<CCPoint> MatchesList_t;

class MatrixField
{
private:
	static const int	m_MaxFieldSize		= 100;
	static const int	m_MaxVisibleSize	= 10;
	static const int	m_MaxTypesCount		= 4;
	int					m_Field[m_MaxFieldSize][m_MaxFieldSize];
protected:
public:
    MatrixField();
    virtual ~MatrixField();

	void				GenerateField(bool isRegenerate = false);
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

	MatchesList_t GetFirstMatches();
};
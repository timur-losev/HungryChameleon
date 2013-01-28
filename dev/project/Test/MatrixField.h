#pragma once
#include <assert.h>
#include <vector>
#include <cocos2d.h>
using namespace cocos2d;

typedef std::vector<CCPoint> MatchesList_t;

class MatrixField
{
private:
	static int	m_MaxFieldSize;
	static int	m_MaxVisibleSize;
	static int	m_MaxTypesCount;
	int**		m_Field;
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
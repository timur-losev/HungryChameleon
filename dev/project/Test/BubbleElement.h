#pragma once
#include <cocos2d.h>
using namespace cocos2d;

class BubbleElement: public CCSprite
{
private:
	typedef std::map<int, std::vector<CCRect>>	BubbleMap_t;
	static BubbleMap_t							m_BubblesMap;
	int											m_Type;

	static const int							m_BubbleSize = 35;
protected:
public:
    BubbleElement(int type);
    ~BubbleElement();

	void										SetType(int type);
	inline int									GetType() { return m_Type; }

	static inline int							GetBubbleSize() { return m_BubbleSize; }

	static void									FakeBubblesInit();

private:
	BubbleElement();
	BubbleElement(const BubbleElement& oth);
};


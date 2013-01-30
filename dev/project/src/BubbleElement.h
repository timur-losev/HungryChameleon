#pragma once

class BubbleElement: public CCSprite
{
private:
	static int									m_BubbleSize;	//Temp values
	static float								m_BubbleScale;	//Temp values
	static std::string							m_Texture;

	typedef std::map<int, std::vector<CCRect>>	BubbleMap_t;
	static BubbleMap_t							m_BubblesMap;
	int											m_Type;
protected:
public:
    BubbleElement(int type);
    ~BubbleElement();

	void										SetType(int type);
	inline int									GetType() { return m_Type; }

	static inline int							GetBubbleSize() { return m_BubbleSize * m_BubbleScale; }

	static void									FakeBubblesInit();
	static bool									LoadBubbles();

private:
	BubbleElement();
	BubbleElement(const BubbleElement& oth);
};

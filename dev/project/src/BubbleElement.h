#pragma once

class BubbleElement: public CCSprite
{
private:
	static int									m_BubbleSize;	//Temp values
	static float								m_BubbleScale;	//Temp values
	static std::string							m_Texture;
	static int									m_Duration;

	typedef std::map<int, std::vector<CCRect>>	BubbleMap_t;
	static BubbleMap_t							m_BubblesMap;
	int											m_Type;
	size_t										m_FrameIndx;
	unsigned long								m_LastAnimationTime;
protected:
public:
    BubbleElement(int type);
    ~BubbleElement();

	void										SetType(int type);
	inline int									GetType() { return m_Type; }

	void										Update(float dt);

	static inline int							GetBubbleSize() { return (int)(m_BubbleSize * m_BubbleScale); }
	static void									FakeBubblesInit();
	static bool									LoadBubbles();

private:
	BubbleElement();
	BubbleElement(const BubbleElement& oth);
};


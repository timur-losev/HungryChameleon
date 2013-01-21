#include "BubbleElement.h"
#include "VisibleRect.h"
#include "MatrixField.h"

BubbleElement::BubbleMap_t BubbleElement::m_BubblesMap;

BubbleElement::BubbleElement(int type)
	: m_Type(type)
{
	if (m_BubblesMap.find(type) != m_BubblesMap.end())
	{
		CCRect rect = m_BubblesMap[type][0];
		this->initWithFile("data/cubes.png");
		this->setTextureRect(rect);
	}
}

BubbleElement::~BubbleElement()
{

}

void BubbleElement::SetType(int type)
{
	if (m_BubblesMap.find(type) != m_BubblesMap.end())
	{
		CCRect rect = m_BubblesMap[type][0];
		this->setTextureRect(rect);

		m_Type = type;
	}
	else
	{
		int k =0;
	}
}

void BubbleElement::FakeBubblesInit()
{
	for(int j = 0; j < MatrixField::GetMaxTypes(); ++j)
	{
		std::vector<CCRect> animFrames;
		animFrames.push_back(CCRectMake(0, j * 45, m_BubbleSize, m_BubbleSize));

		m_BubblesMap[j] = animFrames;
	}
}
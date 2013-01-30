#include "pch.h"
#include "BubbleElement.h"
#include "VisibleRect.h"
#include "MatrixField.h"
#include "CSystem.h"
#include "Utils.h"
#include <map>

int BubbleElement::m_BubbleSize = 40;
float BubbleElement::m_BubbleScale = 1.3f;
std::string BubbleElement::m_Texture;
BubbleElement::BubbleMap_t BubbleElement::m_BubblesMap;

BubbleElement::BubbleElement(int type)
	: m_FrameIndx(0)
{
	m_LastAnimationTime = CSystem::GetTickCount();

	if (m_BubblesMap.find(type) != m_BubblesMap.end())
	{
		this->initWithFile(m_Texture.c_str());
		SetType(type);
	}
}

BubbleElement::~BubbleElement()
{
	m_BubblesMap.clear();
}

void BubbleElement::SetType(int type)
{
	if (type == m_Type)
	{
		return;
	}

	if (m_BubblesMap.find(type) != m_BubblesMap.end())
	{
		m_FrameIndx = 0;

		CCRect rect = m_BubblesMap[type][m_FrameIndx];		
		this->setTextureRect(rect);
		this->setAnchorPoint(CCPointMake(0.0f, 0.0f));
		this->setScale(m_BubbleScale);

		m_Type = type;
	}
}

void BubbleElement::FakeBubblesInit()
{
	m_Texture = CSystem::GetBundlePath() + std::string("data/bubbles.png");

	for(int j = 0; j < MatrixField::GetMaxTypes() + 1; ++j)
	{
		std::vector<CCRect> animFrames;
		animFrames.push_back(CCRectMake(j * m_BubbleSize, 0, m_BubbleSize, m_BubbleSize));

		m_BubblesMap[j] = animFrames;
	}
}

bool BubbleElement::LoadBubbles()
{
	std::string fullname = CSystem::GetBundlePath() + "data/bubbles.xml";

	TiXmlDocument doc(fullname.c_str());
    doc.LoadFile();
    TiXmlElement* root = doc.RootElement();
	if (!root)
	{
		return false;
	}

	TiXmlElement* xsettings = root->FirstChildElement("Settings");
	if (!xsettings)
	{
		return false;
	}
	m_Texture = CSystem::GetBundlePath() + std::string("data/") + std::string(xsettings->Attribute("texture"));
	xsettings->Attribute("size", &m_BubbleSize);
	xsettings->Attribute("scale", &m_BubbleScale);

	std::map<std::string, CCRect> frames;
	TiXmlElement* xframe = root->FirstChildElement("Frame");
	while(xframe)
	{
		CCRect rect;
		xframe->Attribute("x", &rect.origin.x);
		xframe->Attribute("y", &rect.origin.y);
		xframe->Attribute("w", &rect.size.width);
		xframe->Attribute("h", &rect.size.height);

		std::string name = xframe->Attribute("name");

		frames[name] = rect;

		xframe = xframe->NextSiblingElement("Frame");
	}

	int type = 0; // TODO: temp
	TiXmlElement* xanim = root->FirstChildElement("Anim");
	while(xanim)
	{
		std::vector<CCRect> framesList;
		std::vector<std::string> strFramesList;
		std::string strFrames = xanim->Attribute("frames");

		Utils::SplitString(strFrames, ",", strFramesList);

		size_t frameCount = strFramesList.size();
		framesList.resize(frameCount);
		for (size_t i = 0; i < frameCount; ++i)
		{
			framesList[i] = frames[strFramesList[i]];
		}

		m_BubblesMap[type] = framesList;
		++type;

		xanim = xanim->NextSiblingElement("Anim");
	}

	return true;
}

void BubbleElement::Update(float dt)
{
	if (CSystem::GetTickCount() - m_LastAnimationTime > 300)
	{
		if (m_FrameIndx < m_BubblesMap[m_Type].size())
		{
			CCRect rect = m_BubblesMap[m_Type][m_FrameIndx];		
			this->setTextureRect(rect);

			++m_FrameIndx;
			if (m_FrameIndx >= m_BubblesMap[m_Type].size())
			{
				m_FrameIndx = 0;
			}

			m_LastAnimationTime = CSystem::GetTickCount();
		}
	}
}
#include "Precompiled.h"
#include "BubbleSet.h"

#include "BubbleElement.h"
#include "MatrixField.h"

#include "Utils.h"
#include "System.h"

BubbleSet::BubbleSet()
{

}

BubbleSet::~BubbleSet()
{
    std::for_each(m_elements.begin(), m_elements.end(), [](BubblesLine_t& line)
    {
        std::for_each(line.begin(), line.end(), [](BubbleElement* elem)
        {
            elem->release();
        });
    });
}

bool BubbleSet::loadBubbles()
{
    std::string fullname = System::GetResourcesPath() + "spiders2.xml";

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
    m_texture = System::GetResourcesPath() + std::string(xsettings->Attribute("texture"));

    {
        xsettings->Attribute("size", &m_bubbleSize);
        xsettings->Attribute("scale", &m_bubbleScale);
        xsettings->Attribute("duration", &m_duration);
    }

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

        m_bubblesMap[type] = framesList;
        ++type;

        xanim = xanim->NextSiblingElement("Anim");
    }

    return true;
}

void BubbleSet::fakeBubblesInit()
{
    m_texture = System::GetResourcesPath() + std::string("bubbles.png");

    for(int j = 0; j < MatrixField::k_MaxTypesCount + 1; ++j)
    {
        std::vector<CCRect> animFrames;
        animFrames.push_back(CCRectMake(j * m_bubbleSize, 0, m_bubbleSize, m_bubbleSize));

        m_bubblesMap[j] = animFrames;
    }
}

uint32_t BubbleSet::getBubbleSize() const
{
    return (uint32_t)((float)m_bubbleSize * m_bubbleScale);
}

void BubbleSet::pushElement( const BubblesLine_t& elem )
{
    m_elements.push_back(elem);
}

BubbleElement* BubbleSet::getElementAt( uint32_t x, uint32_t y ) const
{
    assert(x < m_elements.size() && y < m_elements[x].size());

    return m_elements[x][y];
}

BubbleElement* BubbleSet::getElementAt( const CCPoint& p ) const
{
    return getElementAt(static_cast<uint32_t>(p.x), static_cast<uint32_t>(p.y));
}

void BubbleSet::updateBubble( float dt, BubbleElement* bubble )
{
    const int type = bubble->getType();
    size_t frameIndex = bubble->getFrameIndex();

    assert(m_bubblesMap.find(type) != m_bubblesMap.end());

    if (System::GetTickCount() - bubble->getLastAnimationTime() > m_duration)
    {
        const auto& rectLine = m_bubblesMap[type];

        if (frameIndex < rectLine.size())
        {
            const CCRect& rect = rectLine[frameIndex];
            bubble->setTextureRect(rect);

            ++frameIndex;
            if (frameIndex >= rectLine.size())
            {
                frameIndex = 0;
            }

            bubble->setFrameIndex(frameIndex);

            bubble->setLastAnimationTime(System::GetTickCount());
        }
    }
}

void BubbleSet::setBubbleType( BubbleElement* bubble, int type ) const
{
    bubble->setAnchorPoint(CCPointMake(0, 0));
    bubble->setScale(m_bubbleScale);
    if (type != bubble->getType())
    {
        if (m_bubblesMap.find(type) != m_bubblesMap.end())
        {
            bubble->setFrameIndex(0);
            bubble->setType(type);

            BubblesMap_t::const_iterator it = m_bubblesMap.find(type);

            const CCRect& rect = it->second[0];
            bubble->setTextureRect(rect);
        }
    }
}

BubbleElement* BubbleSet::createBubble( int type ) const
{
    BubbleElement* bubble = new BubbleElement();
    if (m_bubblesMap.find(type) != m_bubblesMap.end())
    {
        bubble->initWithFile(m_texture.c_str());
        setBubbleType(bubble, type);

        return bubble;
    }

    assert("No bubble created" && false);
    return nullptr;
}

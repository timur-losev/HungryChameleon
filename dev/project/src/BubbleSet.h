#pragma once

class BubbleElement;

class BubbleSet
{
public:

    typedef std::vector<BubbleElement*> BubblesLine_t;
    typedef std::vector<BubblesLine_t>  BubbleElements_t;

private:
    typedef std::map<int, std::vector<CCRect>> BubblesMap_t;

    BubblesMap_t            m_bubblesMap;

    uint32_t                m_bubbleSize;   //Temp values
    float                   m_bubbleScale;  //Temp values
    std::string             m_texture;
    uint32_t                m_duration;
    BubbleElements_t        m_elements;

public:
    BubbleSet();
    ~BubbleSet();

    bool                    loadBubbles();
    void                    fakeBubblesInit();
    uint32_t                getBubbleSize() const;

    void                    pushElement(const BubblesLine_t& line);

    BubbleElement*          getElementAt(const CCPoint& p) const;
    BubbleElement*          getElementAt(uint32_t x, uint32_t y) const;

    void                    updateBubble(float dt, BubbleElement* bubble);
    void                    setBubbleType(BubbleElement* bubble, int type) const;
    BubbleElement*          createBubble(int type) const;
};
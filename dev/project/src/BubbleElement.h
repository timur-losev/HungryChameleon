#pragma once

class BubbleElement: public CCSprite
{
private:

    int                     m_Type;
    size_t                  m_FrameIndx;
    unsigned long           m_LastAnimationTime;
protected:
public:
    BubbleElement();
    ~BubbleElement();

    void                    setType(int type);
    inline int              getType() const { return m_Type; }

    unsigned long           getLastAnimationTime() const { return m_LastAnimationTime; }
    void                    setLastAnimationTime(unsigned long val) { m_LastAnimationTime = val; }

    size_t                  getFrameIndex() const { return m_FrameIndx; }
    void                    setFrameIndex(size_t i) { m_FrameIndx = i; }
};

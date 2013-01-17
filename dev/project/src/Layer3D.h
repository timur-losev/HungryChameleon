#pragma once

class Layer3D : public CCLayer
{
private:
protected:
    CCTexture2D*            m_pTexture;
    float                   m_fYav, m_fPitch, m_fRoll;
    float                   m_fSpeed;
public:
    Layer3D();
    virtual ~Layer3D();

    static Layer3D*         create();

    bool                    init();
    virtual void            draw();
    virtual void            update(float fDelta);
};
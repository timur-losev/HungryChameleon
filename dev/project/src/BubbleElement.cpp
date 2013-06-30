#include "Precompiled.h"
#include "BubbleElement.h"
#include "VisibleRect.h"
#include "MatrixField.h"
#include "System.h"
#include "Utils.h"

BubbleElement::BubbleElement()
    : m_FrameIndx(0),
    m_Type(0),
    m_LastAnimationTime(0)
{
    m_LastAnimationTime = System::GetTickCount();
}

BubbleElement::~BubbleElement()
{

}

void BubbleElement::setType( int type )
{
    m_Type = type;
}

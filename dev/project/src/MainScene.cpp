#include "Precompiled.h"
#include "MainScene.h"
#include "VisibleRect.h"
#include "IngameMenuView.h"
#include "GameDelegate.h"
#include "Layer3D.h"
#include "ParallaxBackground.h"
#include "BubbleElement.h"
#include "System.h"

#include "BubbleSet.h"
#include "MatrixField.h"

MainScene::MainScene()
    : m_pBackground(0)
    , m_LabelTimer(0)
    , m_MatchDuration(60000)
{
    LoadGameSettings();

    m_QuickScrollPos = CCPointMake(-1, -1);
    m_MatchStartTime = System::GetTickCount();

    m_BubbleSet.reset(new BubbleSet());
    m_MatrixField.reset(new MatrixField());
}

MainScene::~MainScene()
{
    m_pBackground->removeAllChildrenWithCleanup(true);
}

bool MainScene::init()
{
    bool kRet = GameSceneBase::init();

    m_pBackground = ParallaxBackground::create();
    m_pBackground->RegisterTouchBeganCallback(std::bind(&MainScene::OnTouchEnded, this, std::placeholders::_1));
    m_pBackground->RegisterTouchMovedCallback(std::bind(&MainScene::OnTouchMoved, this, std::placeholders::_1));

    IngameMenuView* igmenu = new IngameMenuView();
    igmenu->init();
    igmenu->getBackToMainMenu()->setTarget(this, menu_selector(MainScene::onMainMenuTap));

    // Counter
    m_LabelTimer = CCLabelTTF::create("Time: 1:00", "data/brookeshappelldots.ttf", 68);
    m_LabelTimer->setPosition(CCPointMake(m_LabelTimerPos.x, VisibleRect::top().y - m_LabelTimerPos.y));

    m_LabelScores = CCLabelTTF::create("Score: 0000000", "data/brookeshappelldots.ttf", 68);
    m_LabelScores->setPosition(CCPointMake(m_ScoresTimerPos.x, VisibleRect::top().y - m_ScoresTimerPos.y));

    addChild(m_pBackground);
    addChild(igmenu);
    addChild(m_LabelTimer);
    addChild(m_LabelScores);

    igmenu->release();

    return kRet;
}

void MainScene::onEnter()
{
    GameSceneBase::onEnter();

    m_BubbleSet->loadBubbles();

    m_ScoresCount = 0;

    m_MatrixField->generateField();
    BubbleSet::BubblesLine_t line;
    line.resize(MatrixField::k_MaxVisibleSize);

    for(int i = 0; i < MatrixField::k_MaxVisibleSize; ++i)
    {
        for(int j = 0; j < MatrixField::k_MaxVisibleSize; ++j)
        {
            const uint32_t bubbleSize = m_BubbleSet->getBubbleSize();
            int x = m_BubbleViewDisplacement.x + i * (bubbleSize + m_SpaceBetweenBubbles);
            int y = VisibleRect::top().y - m_BubbleViewDisplacement.y - bubbleSize - j * (bubbleSize + m_SpaceBetweenBubbles);

            BubbleElement* element = m_BubbleSet->createBubble( m_MatrixField->getVisible(i, j) );//rand() % MatrixField::GetMaxTypes() );
            element->setPosition( ccp( x, y ) );

            m_pBackground->addChild(element);

#pragma message ("make sure the reference is correct")
            //element->retain();

            line[j] = element;
        }

        m_BubbleSet->pushElement(line);
    }

    schedule(schedule_selector(MainScene::onUpdate), 0.0f);
}

void MainScene::onMainMenuTap( CCObject* )
{
    SharedGameDelegate::Instance().returnToMainMenu();
}

void MainScene::OnTouchEnded(CCTouch* touch)
{
    int direction;
    if (abs(m_QuickScrollDelta.x) > abs(m_QuickScrollDelta.y))
    {
        direction = (m_QuickScrollDelta.x >= 0) ? -2 : -1;
    }
    else
    {
        direction = (m_QuickScrollDelta.y >= 0) ? 0 : 1;
    }

    m_MatrixField->scroll(direction, m_QuickScrollPos.x, m_QuickScrollPos.y);
    m_QuickScrollPos = CCPointMake(-1, -1);
}

void MainScene::OnTouchMoved(CCTouch* touch)
{
    CCPoint delta = touch->getDelta();
    CCPoint position = touch->getLocationInView();


    const int visible = MatrixField::k_MaxVisibleSize;
    const uint32_t bubbleSize = m_BubbleSet->getBubbleSize();

    int fieldSizeX = m_BubbleViewDisplacement.x + visible * (bubbleSize + m_SpaceBetweenBubbles);
    int fieldSizeY = m_BubbleViewDisplacement.y + visible * (bubbleSize + m_SpaceBetweenBubbles);

    if (position.x < m_BubbleViewDisplacement.x || 
        position.y < m_BubbleViewDisplacement.y ||
        position.x >= fieldSizeX || 
        position.y >= fieldSizeY ||
        (delta.x == 0 && delta.y == 0))
    {
        // Scroll parallax background
        m_pBackground->Scroll(touch);
        return;
    }

    position.x -= m_BubbleViewDisplacement.x;
    position.y -= m_BubbleViewDisplacement.y;

    int yPos = (int)(position.x / (bubbleSize + m_SpaceBetweenBubbles));
    int xPos = (int)(position.y / (bubbleSize + m_SpaceBetweenBubbles));

    if (m_QuickScrollPos.x == -1 && m_QuickScrollPos.y == -1)
    {
        m_QuickScrollPos	= CCPointMake(xPos, yPos);
        m_QuickScrollVertical = abs(delta.x) > abs(delta.y);
    }

    if (m_QuickScrollVertical)
    {
        delta.y = 0;
        delta.x = (bubbleSize * ((delta.x >= 0) ? 1.0f : -1.0f)) / 2.0f;
    }
    else
    {
        delta.x = 0;
        delta.y = (bubbleSize * ((delta.y >= 0) ? 1.0f : -1.0f)) / 2.0f;
    }

    m_QuickScrollDelta = delta;
}

void MainScene::onUpdate(float dt)
{
    unsigned int currentTime = System::GetTickCount() / 1000;
    if (currentTime < m_MatchStartTime / 1000 + m_MatchDuration)
    {
        int timeLeft = (int)(m_MatchStartTime / 1000 + m_MatchDuration - currentTime);
        int hour = timeLeft / 60;
        int sec =  (timeLeft - (hour * 60));

        char strTime[64];
        sprintf(strTime, "Time: %d:%.2d", hour, sec);
        m_LabelTimer->setString(strTime);
    }
    else
    {
        // Game Over
        SharedGameDelegate::Instance().returnToMainMenu();
    }

    UpdateMatrix(dt);

    static bool needMatrixScroll = false;
    static unsigned long lastTimeUpdateMatrix = System::GetTickCount();
    if (System::GetTickCount() - lastTimeUpdateMatrix > 250)
    {
        lastTimeUpdateMatrix = System::GetTickCount();

        MatrixField::MatchesList_t matches = m_MatrixField->getFirstMatches();
        PushFlyingBubbles(matches);

        if (matches.empty() && needMatrixScroll)
        {
            m_MatrixField->scrollDown();
        }
        else if (!matches.empty() && !needMatrixScroll)
        {
            needMatrixScroll = true;
        }

        m_ScoresCount += matches.size() * 50;

        char strScore[128];
        sprintf(strScore, "Score: %.7d", m_ScoresCount);
        m_LabelScores->setString(strScore);
    }
}

void MainScene::UpdateMatrix(float dt)
{
    for(int i = 0; i < MatrixField::k_MaxVisibleSize; ++i)
    {
        for(int j = 0; j < MatrixField::k_MaxVisibleSize; ++j)
        {
            BubbleElement* element = m_BubbleSet->getElementAt(i, j);

            int type = m_MatrixField->getVisible(i, j);
            if (type >= 0)
            {
                element->setType(type);
                element->setVisible(true);
                element->setOpacity(255);
            }
            else
            {
                //element->setVisible(false);
                element->setOpacity(128);
            }

            // additional shift for row or column
            const uint32_t bubbleSize = m_BubbleSet->getBubbleSize();
            int x = m_BubbleViewDisplacement.x + i * (bubbleSize + m_SpaceBetweenBubbles);
            int y = VisibleRect::top().y - m_BubbleViewDisplacement.y - bubbleSize - j * (bubbleSize + m_SpaceBetweenBubbles);

            if ((i == m_QuickScrollPos.y && !m_QuickScrollVertical) || (j == m_QuickScrollPos.x && m_QuickScrollVertical))
            {
                x += m_QuickScrollDelta.x;
                y += m_QuickScrollDelta.y;
            }

            element->setPosition( ccp( x, y ) );

            m_BubbleSet->updateBubble(dt, element);
        }
    }
}

bool MainScene::LoadGameSettings()
{
    std::string fullname = System::GetBundlePath() + "data/game_settings.xml";

    TiXmlDocument doc(fullname.c_str());
    doc.LoadFile();
    TiXmlElement* root = doc.RootElement();
    if (!root)
    {
        return false;
    }

    TiXmlElement* xglobal = root->FirstChildElement("Global");
    TiXmlElement* xbubbleField = root->FirstChildElement("BubblesField");
    TiXmlElement* xtimeField = root->FirstChildElement("TimeField");
    TiXmlElement* xscoresField = root->FirstChildElement("ScoresField");
    TiXmlElement* xflyingBubbles = root->FirstChildElement("FlyingBubbles");
    if (!xglobal ||
        !xbubbleField ||
        !xtimeField ||
        !xscoresField ||
        !xflyingBubbles)
    {
        return false;
    }
    xbubbleField->Attribute("x", &m_BubbleViewDisplacement.x);
    xbubbleField->Attribute("y", &m_BubbleViewDisplacement.y);
    xbubbleField->Attribute("space_between_bubbles", &m_SpaceBetweenBubbles);
    xglobal->Attribute("duration_of_match", &m_MatchDuration);
    xtimeField->Attribute("x", &m_LabelTimerPos.x);
    xtimeField->Attribute("y", &m_LabelTimerPos.y);
    xscoresField->Attribute("x", &m_ScoresTimerPos.x);
    xscoresField->Attribute("y", &m_ScoresTimerPos.y);

    return true;
}

void MainScene::PushFlyingBubbles(const MatrixField::MatchesList_t& bubbles)
{
    size_t size = bubbles.size();
    for (size_t i = 0; i < size; ++i)
    {
        CCPointArray *array = CCPointArray::create(20);

        const uint32_t bubbleSize = m_BubbleSet->getBubbleSize();

        int x = m_BubbleViewDisplacement.x + bubbles[i].y * (bubbleSize + m_SpaceBetweenBubbles);
        int y = VisibleRect::top().y - m_BubbleViewDisplacement.y - bubbleSize - bubbles[i].x * (bubbleSize + m_SpaceBetweenBubbles);

        array->addControlPoint(ccp(x, y));
        array->addControlPoint(ccp(x + 30, y + 30));
        array->addControlPoint(ccp(x + 60, y + 50));
        array->addControlPoint(ccp(x + 80, y + 70));
        array->addControlPoint(ccp(750, 400));

        CCCardinalSplineTo *action = CCCardinalSplineTo::create(1.5, array, 0);
        CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(MainScene::RemoveFlyingBubbles));
        CCFiniteTimeAction *seq = CCSequence::create(action, actionMoveDone, NULL);

        BubbleElement* bubble = m_BubbleSet->createBubble(m_BubbleSet->getElementAt(bubbles[i])->getType());

        bubble->setPosition(CCPointMake(x, y));
        bubble->runAction(seq);
        addChild(bubble);
    }
}

void MainScene::RemoveFlyingBubbles(CCNode* sender)
{
    BubbleElement *sprite = static_cast<BubbleElement*>(sender);
    removeChild(sprite, true);
}
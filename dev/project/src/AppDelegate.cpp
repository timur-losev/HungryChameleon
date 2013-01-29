#include "pch.h"

#include "AppDelegate.h"
#include "GameController.h"

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

    CCSize designSize = CCSizeMake(1024, 768);
    
    if (screenSize.height > 640)
    {
        //TODO
        CCSize resourceSize = CCSizeMake(7024, 768);
        CCFileUtils::sharedFileUtils()->setResourceDirectory("data");
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
    }
    else
    {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("data");
    }

    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionNoBorder);

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    m_pGameController = new GameController();
    m_pGameController->autorelease();
    if (!m_pGameController->init())
        return false;
    m_pGameController->showMainMenu();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    /*SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();*/
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    /*SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();*/
}
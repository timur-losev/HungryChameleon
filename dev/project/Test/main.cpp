#include <iostream>
#include <cocos2d.h>
#include "AppDelegate.h"

using namespace cocos2d;

int APIENTRY WinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(960, 640);
    return CCApplication::sharedApplication()->run();
}
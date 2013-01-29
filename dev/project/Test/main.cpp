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
    eglView->setFrameSize(1024, 768);
    return CCApplication::sharedApplication()->run();
}
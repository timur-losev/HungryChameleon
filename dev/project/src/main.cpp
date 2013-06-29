#include "Precompiled.h"
#include "AppDelegate.h"

#include "GameDelegate.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(1024, 768);

    SharedGameDelegate::Instance().init();

    return CCApplication::sharedApplication()->run();

    return 0;
}
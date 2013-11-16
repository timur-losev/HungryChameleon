#include "Precompiled.h"
#include "AppDelegate.h"

#include "GameDelegate.h"

#if 0
int APIENTRY WinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
#else
int main()
#endif
{

    /*UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);*/

    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(1024, 768);

    SharedGameDelegate::Instance().init();

    return CCApplication::sharedApplication()->run();

    return 0;
}
/* 
 * File:   CTexture.cpp
 * Author: yevgeniy.logachev
 * 
 * Created on September 11, 2012, 5:00 PM
 */
#include "pch.h"
#include "CSystem.h"

#if defined(OS_IPHONE)
#import "CoreFoundation/CoreFoundation.h"
#include <sys/time.h>
#elif defined(LINUX)
#include <sys/time.h>
#elif defined(WIN32)
#include <windows.h>
#endif
#include <io.h>

unsigned long CSystem::GetTickCount()
{
#if defined(OS_IPHONE) || defined(LINUX)
    struct timeval t;
    gettimeofday( &t, 0 );
    return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
#elif defined(WIN32)
	return (unsigned long)::GetTickCount();
#endif
    
    return 0;
} 

const std::string& CSystem::GetBundlePath()
{
    static std::string bundlePath = "";
    
    if (bundlePath.empty())
    {
#if defined(OS_IPHONE)
        NSString* path = [[NSBundle mainBundle] resourcePath];
        
        bundlePath = std::string([path UTF8String]) + std::string("/");// + std::string("/../Documents/");
#endif
    }
    
    return bundlePath;
}

bool CSystem::IsFileExists( const std::string& name ){
	return _access( name.c_str(), 0 ) != -1;
}


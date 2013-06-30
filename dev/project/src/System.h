/* 
 * File:   CTexture.h
 * Author: yevgeniy.logachev
 *
 * Created on September 11, 2012, 5:00 PM
 */

#ifndef CSYSTEM_H
#define	CSYSTEM_H

namespace System
{
    unsigned long GetTickCount();
    
    const std::string& GetBundlePath();
	const std::string& GetResourcesPath();
	bool IsFileExists( const std::string& name );
};

#endif	/* CSYSTEM_H */


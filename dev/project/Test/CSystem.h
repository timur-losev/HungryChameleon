/* 
 * File:   CTexture.h
 * Author: yevgeniy.logachev
 *
 * Created on September 11, 2012, 5:00 PM
 */

#ifndef CSYSTEM_H
#define	CSYSTEM_H

#include <string>

namespace CSystem
{
    unsigned long GetTickCount();
    
    const std::string& GetBundlePath();
	bool IsFileExists( const std::string& name );
};

#endif	/* CSYSTEM_H */


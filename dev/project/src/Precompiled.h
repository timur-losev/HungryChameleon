#pragma once

#include <iostream>

#include <assert.h>

#include <tinyxml.h>
#include <cocos2d.h>
#include <cocos-ext.h>


#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <memory.h>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <deque>

#include <stdlib.h>

#include <unordered_map> 

#include <loki/Singleton.h> // Contains required system headers as well

#include "sigslot.h"

using namespace cocos2d;

#define forward_this_u(__class__)\
class __class__;\
    typedef std::unique_ptr<__class__> __class__##Ptr;\
    typedef std::unique_ptr<__class__ const> __class__##ConstPtr

#define forward_this_su(__class__)\
struct __class__;\
    typedef std::unique_ptr<__class__> __class__##Ptr;\
    typedef std::unique_ptr<__class__ const> __class__##ConstPtr

#define forward_this(__class__)\
class __class__;\
    typedef std::shared_ptr<__class__> __class__##Ptr;\
    typedef std::shared_ptr<__class__ const> __class__##ConstPtr

#define forward_this_s(__class__)\
struct __class__;\
    typedef std::shared_ptr<__class__> __class__##Ptr;\
    typedef std::shared_ptr<__class__ const> __class__##ConstPtr

#define forward_this_w(__class__)\
class __class__;\
    typedef std::weak_ptr<__class__> __class__##WeakPtr;\
    typedef std::weak_ptr<__class__ const> __class__##ConstWeakPtr

#define forward_this_ws(__class__)\
struct __class__;\
    typedef std::weak_ptr<__class__> __class__##WeakPtr;\
    typedef std::weak_ptr<__class__ const> __class__##ConstWeakPtr
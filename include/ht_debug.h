/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#pragma once

//Header includes
#include <string>

//Inline includes
#include <ht_platform.h>
#include <iostream>
#if defined(HT_SYS_WINDOWS)
#include <debugapi.h>
#endif
#include <format.h>

#ifndef HT_STRINGIFY
#define HT_STRINGIFY(x) #x
#endif

#ifndef HT_SFY_
#define HT_SFY_(x) HT_STRINGIFY(x)
#endif

#ifndef HT_SFY_FUNC
#define HT_SFY_FUNC HT_SFY_(__FUNCTION__)
#endif

#ifndef HT_SFY_LINE
#define HT_SFY_LINE HT_SFY_(__LINE__)
#endif
#ifndef HT_SFY_FILE
#define HT_SFY_FILE HT_SFY_(__FILE__)
#endif

#ifndef HT_LOG_FILE
#define HT_LOG_FILE "FILE: " HT_SFY_FILE
#endif
#ifndef HT_LOG_LINE
#define HT_LOG_LINE "LINE: " HT_SFY_LINE
#endif

#ifndef HT_LOG_FUNC
#define HT_LOG_FUNC "FUNC: " __FUNCTION__
#endif

#ifndef HT_LOG_PREFIX
#define HT_LOG_PREFIX HT_LOG_FILE "\n" HT_LOG_FUNC "\n" HT_LOG_LINE "\n"
#endif

#ifndef HT_DEBUG_PRINTF
    #if defined(DEBUG) || defined(_DEBUG)
        #define HT_DEBUG_PRINTF(fmt_string, ...) Hatchit::Core::DebugPrintF(fmt_string, ## __VA_ARGS__);
    #else
        #define HT_DEBUG_PRINTF(fmt_string, ...)
    #endif
#endif

namespace Hatchit {

    namespace Core {

        template<class ... Args> 
        std::string DebugSprintF(const char* format, const Args& ... args);

        template<class ... Args> 
        int DebugPrintF(const char* format, const Args& ... args);
    }
}

#include <ht_debug.inl>
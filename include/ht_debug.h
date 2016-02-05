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

#include <ht_platform.h>
#include <ht_string.h>
#include <iostream>
#include <iomanip>

#ifdef HT_SYS_LINUX
#include <cstdarg>
#endif

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

namespace Hatchit {

    namespace Core {


        /*! \brief Function implements variable formatted argument debug print
        *
        *
        *  This debug utility function takes in a user format string and
        *  a variable argument list, then prints the formatted string result
        *  to the console
        *  @param format The format string
        *  @param argList the argument list used with format string
        */
        inline int VDebugPrintF(const char* format, va_list argList)
        {
            static char s_buffer[HT_BUFSIZE];
            int written = -1;

            #ifdef HT_SYS_WINDOWS
                written = vsnprintf_s(s_buffer, HT_BUFSIZE, format, argList);
            #else
                written = vsnprintf(s_buffer, sizeof(s_buffer), format, argList);
            #endif

            #ifdef HT_SYS_WINDOWS
                //Call Win32 debug output to pump message to
                //Visual Studio console
                OutputDebugStringA(s_buffer);
            #endif

            std::cerr << s_buffer;

            return written;
        }

        /*! \brief Function takes a formatted string and arguments to print
        *
        *
        *  This debug utility function takes in a user format string and
        *  a variable argument list, then prints the formatted string result
        *  to the console
        *  @param format The format string
        *  @param ... the argument list used with format string
        */
        inline int DebugPrintF(const char* format, ...)
        {
            va_list argList;
            va_start(argList, format);

            int written = VDebugPrintF(format, argList);

            va_end(argList);

            return written;
        }

    }

}

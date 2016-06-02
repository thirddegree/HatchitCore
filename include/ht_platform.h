/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
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

/////////////////////////////////////////////////////////////
// Define portable platform macros
/////////////////////////////////////////////////////////////

#ifdef _WIN32
    /**
    \def HT_SYS_WINDOWS
    \brief Using Windows platform
    **/
#   define HT_SYS_WINDOWS

    /**
    \def WIN32_LEAN_AND_MEAN
    \brief Used to help stop namespace pollution

    Helps stop pollution of the C namespace as well
    as the macro namespace.
    **/
#   define WIN32_LEAN_AND_MEAN
#   include <windows.h>
#   include <winapifamily.h>
#   ifndef NOMINMAX

    /**
    \def NOMINMAX
    \brief Prevents precompiler minmax from being defined

    Prevents precompiler minmax from being defined, allowing
    use of std::min and std::max
    **/
#   define NOMINMAX
#   endif

#   if defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
        /*include headers for Universal Windows PC Application*/
#       include <wrl.h>
#       include <concrt.h>
#   endif
#elif defined(__linux__)
    /**
    \def HT_SYS_LINUX
    \brief Using Linux platform
    **/
#   define HT_SYS_LINUX
#elif defined(__APPLE__)
    /**
    \def HT_SYS_MACOS
    \brief Using Mac OS platform (Apple)
    **/
#   define HT_SYS_MACOS
#else
#   error System is not suported by Hatchit
#endif

/////////////////////////////////////////////////////////////
// Define portable API import/export macros
/////////////////////////////////////////////////////////////

#if !defined(HT_STATIC)
#   ifdef HT_SYS_WINDOWS
        //define dllexport and dllimport macros
#       if defined (HT_NONCLIENT_BUILD)
#           ifndef HT_API
            /**
            \def HT_API
            \brief defined portable API import and export

            Allows Hatchit to easily switch between defining
            export and import functions
            **/
#           define HT_API __declspec(dllexport)
#           endif
#       else
#           ifndef HT_API
            /**
            \def HT_API
            \brief defined portable API import and export

            Allows Hatchit to easily switch between defining
            export and import functions
            **/
#           define HT_API __declspec(dllimport)
#           endif
#       endif

        //Visual C++ compiler warning C4251 disable
#       ifdef _MSC_VER
#       pragma warning(disable : 4251)
#       pragma warning(disable : 4275)
        #pragma warning(disable : 4996)
#       endif

#   else //Linux and MAC OSX
#       if __GNUC__ >= 4
            //GCC 4 has unique keywords for showing/hiding symbols
            //the same keyword is used for both import and export
            /**
            \def HT_API
            \brief defined portable API import and export

            Allows Hatchit to easily switch between defining
            export and import functions
            **/
#           define HT_API __attribute__((__visibility__("default")))
            
#           ifndef __forceinline
            /**
            \def __forceinline
            \brief Define __forceinline for use with GCC

            Define MSVC compatible __forceinline keyword
            for use with GCC compiler.
            **/
#           define __forceinline //__attribute__((always_inline))
#           endif

#       else
#           define HT_API
#       endif
#   endif
#else
    //static build doesn't need import/export macros
#   define HT_API
#endif

#ifndef _MSC_VER

/**
\def NOEXCEPT
\brief Defines function that does not throw exceptions

Place at the end of function declarations to define a function
that guarantees an exception will not be thrown.
**/
#define NOEXCEPT noexcept
#elif _MSC_VER >= 1900

/**
\def NOEXCEPT
\brief Defines function that does not throw exceptions

Place at the end of function declarations to define a function
that guarantees an exception will not be thrown.
**/
#define NOEXCEPT noexcept
#else

/**
\def NOEXCEPT
\brief Defines function that does not throw exceptions

Place at the end of function declarations to define a function
that guarantees an exception will not be thrown.
**/
#define NOEXCEPT 
#endif

//////////////////////////////
// BYTE typedef
//////////////////////////////

/**
\typedef BYTE
\brief Defines variable length of a single byte

Defines a variable of a single byte length.  Useful
for functions that take general data streams.
**/
using BYTE = unsigned char;

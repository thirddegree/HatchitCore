#pragma once

#include <ht_debug.h>

namespace Hatchit
{
    namespace Core
    {
        /*! \fn std::string DebugSprintF(const char* format, const Args& ... args) 
        * \brief Function takes a formatted string and arguments to format into a string.
        *
        *
        *  This debug utility function takes in a user format string and
        *  a variable argument list, then prints the formatted string result
        *  to the console.
        *  @param format The format string.
        *  @param args The argument list used with format string.
        */
        template<class ... Args>
        inline std::string DebugSprintF(const char* format, const Args& ... args)
        {
            return fmt::sprintf(format, args ...);
        }

        /*! \fn size_t DebugPrintF(const char* format, const Args& ... args) 
        * \brief Function takes a formatted string and arguments to print.
        *
        *
        *  This debug utility function takes in a user format string and
        *  a variable argument list, then prints the formatted string result
        *  to the console.
        *  @param format The format string.
        *  @param args The argument list used with format string.
        */
        template<class ... Args>
        inline size_t DebugPrintF(const char* format, const Args& ... args)
        {
            std::string message = fmt::sprintf(format, args ...);

#if defined(HT_SYS_WINDOWS)
            OutputDebugStringA(message.c_str());
#endif

            std::cerr << message.c_str();

            return message.length();
        }
    }
}
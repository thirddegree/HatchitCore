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

#include <ht_platform.h>
#include <string>
#include <cstdint>


/**
*   Unique Identifier Macro
*
*   This macro is used wherever string literals are used but a unique identifier is wanted. The purpose
*   of this macro is to be used to convert the string into the hashed integer value
*   to avoid using actual string comparisons in code.
*
*   NOTE:
*           Currently NOT implemented. There will need to be some sort of preprocess
*           that is run to correctly find each use of the macro and substitute the correct
*           hashed value in place of the string literal.
*
*/
#ifndef HID
#define HID(x) -1
#endif

namespace Hatchit
{
    namespace Core
    {
        /**
        \brief Describes the buffer size to use for C-String operations.
        **/
        constexpr size_t HT_STRINGBUFFSIZE = 1024;

        HT_API std::wstring string_to_wstring (const std::string& str);

        HT_API std::string wstring_to_string (const std::wstring& str);

        HT_API void str_replaceAll(
            std::string& input,
            const std::string& from,
            const std::string& to);

    }

}

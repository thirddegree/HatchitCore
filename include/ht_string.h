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

#include <ht_platform.h> //HT_API
#include <string> //std::string typedef
#include <cstdint> //size_t

namespace Hatchit
{
    namespace Core
    {
        /**
        \brief Describes the buffer size to use for C-String operations.
        **/
        constexpr size_t HT_STRINGBUFFSIZE = 1024;


        HT_API void str_replaceAll(
            std::string& input,
            const std::string& from,
            const std::string& to);

    }

}

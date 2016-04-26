/**
 **    Hatchit Engine
 **    Copyright(c) 2016 Third-Degree
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
#include <json.hpp> //nlohmann::json class
#include <string> //std::string typedef

//Inline includes
#include <ht_guid.h> //Core::Guid
#if defined(_DEBUG) || defined(DEBUG)
#  include <ht_debug.h> //HT_DEBUG_PRINTF
#endif

// Uncomment the following line to disable JSON type checking in release mode
// #define HT_DISABLE_JSON_CHECKS

namespace Hatchit
{
    namespace Core
    {
        /**
         * \brief The JSON type to use.
         */
        using JSON = nlohmann::json;

        /**
         * \brief The verification function used to validate JSON types.
         */
        using JsonVerifyFunc = bool(JSON::*)() const;

        template<typename T>
        bool JsonExtract(
            const JSON& json,
            const std::string& name,
            T& out);
    }
}

#include <ht_jsonhelper.inl>
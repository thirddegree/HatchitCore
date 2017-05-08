/**
**    Hatchit Engine
**    Copyright(c) 2015-2017 Third-Degree
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

namespace Hatchit
{
    namespace Core
    {
        namespace WinRT
        {
            class HT_API Directory
            {
            public:
                static std::string LocalFolder();
                static std::string LocalCacheFolder();
                static std::string RoamingFolder();
                static std::string SharedLocalFolder();
                static std::string TemporaryFolder();
            };
        }
        
    }
}
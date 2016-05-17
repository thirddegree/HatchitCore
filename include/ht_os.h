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

/** \file ht_os.h
* Operating System Utilities

* This file contains utility functions for operating system tasks,
* and each function is defined to be cross platform.
*/

namespace Hatchit
{
    namespace Core
    {

        HT_API void os_mkdir(const std::string& path);

        HT_API bool os_isdir(const std::string& path);

        HT_API std::string os_path(const std::string& path);

        HT_API std::string os_dir(const std::string& path, bool wt = true);

        HT_API std::string os_exec_dir();

        HT_API char	os_path_delimeter();

    }

} 

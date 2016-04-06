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

/** \file ht_os.h
* Operating System Utilities

* This file contains utility functions for operating system tasks,
* and each function is defined to be cross platform.
*/

namespace Hatchit {


    namespace Core {

		/*! \brief Function creates a directory on disk
		*
		*  Creates a directory on the file system with specified path
		*  @param path directory path
		*/
        HT_API void             os_mkdir(const std::string& path);

		/*! \brief Function checks is specified path is a directory
		*
		*  Returns true or false is specified path is a directory
		*  @param path directory path
		*/
        HT_API bool             os_isdir(const std::string& path);

		/*! \brief Function returns os standard path
		*
		*  Returns specified path with correct path delimeters
		*  @param path the system path
		*/
        HT_API std::string      os_path(const std::string& path);

		/*! \brief Function returns the parent directory of a path
		*
		*  @param path system path
		*  @param wt   should include trailing slash
		*/
        HT_API std::string      os_dir(const std::string& path, bool wt = true);

		/*! \brief Function returns the current executable directory
		*
		*/
        HT_API std::string      os_exec_dir();

		/*! \brief Function returns the path delimeter character
		*
		*/
		HT_API char				os_path_delimeter();

    }

} 

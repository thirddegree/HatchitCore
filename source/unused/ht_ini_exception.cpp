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

#include <ht_ini_exception.h>

#include <sstream> //std::stringstream

namespace Hatchit {

    namespace Core {

        /**
        \fn INIException::INIException
        \brief Creates exception with name and description of error.

        Creates an exception with given name and a description of the
        error based on the given error code.
        Valid codes:
            > 0: Parse line error.
            -1: Could not open file.
            default: Memory allocation error.
        **/
        INIException::INIException(std::string name, int error)
        {
            std::stringstream ss;
            ss << "INI Exception: [" << name << "]";
            if (error > 0)
                ss << "--Parse error at line # " << error;
            else if (error == -1)
                ss << "--Could not open file for read";
            else
                ss << "--Memory allocation error";

            m_error = ss.str();
        }

        /**
        \fn INIException::what() const noexcept
        \brief Gives error string.

        Gives error string containing a brief description of
        the error.
        **/
        const char* INIException::what() const NOEXCEPT
        {
            return m_error.c_str();
        }
    }
}
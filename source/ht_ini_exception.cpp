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

#include <ht_ini_exception.h>

namespace Hatchit {

    namespace Core {

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

        const char* INIException::what() const NOEXCEPT
        {
            return m_error.c_str();
        }

    }

}
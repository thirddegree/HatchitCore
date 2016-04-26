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

#include <ht_string.h>

#include <string> //std::string
#include <cstdint> //size_t

namespace Hatchit
{
    namespace Core
    {
        /*!
        * \fn void str_replaceAll(
        *   std::string& input, 
        *   const std::string& from, 
        *   const std::string& to)
        * \brief Function replaces occurences of character in string
        *
        *
        *  This string utility function takes in a user string and replaces
        *  all occurences of a specified character or string with another
        *  @param input The string to modify
        *  @param from  The character or string to replace
        *  @param to    The character or string to replace with
        */
        void str_replaceAll(
            std::string& input, 
            const std::string& from, 
            const std::string& to)
        {
            size_t pos = 0;
            while ((pos = input.find(from, pos)) != std::string::npos) {
                input.replace(pos, from.length(), to);
                pos += to.length();
            }
        }

    }

}

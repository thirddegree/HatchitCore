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


#include <ht_platform.h>
#include <string>
#include <sstream>
#include <vector>

#ifndef HT_BUFSIZE
#define HT_BUFSIZE 1024
#endif

namespace Hatchit {

    namespace Core {


        /*! \brief Function replaces occurences of character in string
        *
        *
        *  This string utility function takes in a user string and replaces
        *  all occurences of a specified character or string with another
        *  @param input The string to modify
        *  @param from  The character to replace
        *  @param to    The character to replace with
        */
        HT_API
        void str_replaceAll(std::string& input,
                            const std::string& from,
                            const std::string& to);

    }

}

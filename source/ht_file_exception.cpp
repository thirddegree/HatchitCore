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

#include <ht_file_exception.h>

#include <ht_string.h> //HT_BUFSIZE

#ifdef HT_SYS_LINUX
#include <cstring>
#endif

namespace Hatchit {

    namespace Core {

        /**
        \fn FileException::FileException(std::string fileName, int error)
        \brief Creates file exception for given file name and error code

        Creates file exception to be thrown with stored error name and
        error description.
        **/
        FileException::FileException(std::string file, int error)
            : std::exception()
        {
#ifdef HT_SYS_WINDOWS
            char errString[HT_STRINGBUFFSIZE];
            strerror_s(errString, HT_STRINGBUFFSIZE, error);
            m_errorString = errString;
#else
            m_errorString = strerror(error);
#endif
            m_whatString = "File Exception: @[" + file + "]--" + m_errorString;
        }

        /**
        \fn FileException::~FileException()
        \brief Destructor is default

        Destructor is default
        **/
        FileException::~FileException() = default;

        /**
        \fn const char* FileException::what()
        \brief Gives description of file exception

        This function returns a C-Style string of a description for the exception.
        **/
        const char* FileException::what() const NOEXCEPT
        {
            return m_whatString.c_str();
        }

    }

}

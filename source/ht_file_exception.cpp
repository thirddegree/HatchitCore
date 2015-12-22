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

#include <ht_file_exception.h>

namespace Hatchit {

    namespace Core {

        FileException::FileException(std::string file, int error)
            : std::exception()
        {
#ifdef HT_SYS_WINDOWS
            char errString[HT_BUFSIZE];
            strerror_s(errString, HT_BUFSIZE, error);
            m_errorString = errString;
#else
            m_errorString = strerror(error);
#endif
            m_whatString = "File Exception: @[" + file + "]--" + m_errorString;
        }

        FileException::~FileException()
        {

        }

        const char* FileException::what() const
        {
            return m_whatString.c_str();
        }

    }

}
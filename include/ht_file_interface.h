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

#include <ht_platform.h> //HT_API
#include <string> //std::string typedef
#include <cstddef> //size_t typedef
#include <cstdio> //FILE typedef
#include <ht_noncopy.h> //INonCopy

namespace Hatchit {

    namespace Core {

        enum class FileSeek
        {
            Current,
            End,
            Set
        };

        enum class FileMode
        {
            ReadText,
            ReadBinary,
            WriteText,
            WriteBinary,
            AppendText,
            AppendBinary
        };

        class HT_API IFile : public INonCopy
        {
        public:
            virtual ~IFile() { };

            virtual std::string Name(void) = 0;
            virtual std::string Path(void) = 0;
            virtual std::string BaseName(void) = 0;
            virtual void        Open(const std::string& path, FileMode mode) = 0;
            virtual bool        Seek(long offset, FileSeek mode) = 0;
            virtual bool        Close(void) = 0;
            virtual size_t      Read(BYTE* out, size_t len) = 0;
            virtual size_t      Write(BYTE* in, size_t len) = 0;
            virtual size_t      Tell(void) = 0;
            virtual size_t      SizeBytes(void) = 0;
            virtual size_t      SizeKBytes(void) = 0;
            virtual size_t      Position(void) = 0;
            virtual FILE*       Handle() = 0;
        };

    }

}
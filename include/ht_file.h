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

//Header includes
#include <ht_platform.h> //HT_API
#include <ht_file_interface.h> //IFile
#include <string> //std::string typedef
#include <cstddef> //size_t typedef
#include <cstdio> //FILE typedef


namespace Hatchit {

    namespace Core {

        class HT_API File : public IFile
        {
        public:
            File(void);

            ~File(void);

            virtual std::string Name(void)                                      override;
            virtual std::string Path(void)                                      override;
            virtual std::string BaseName(void)                                  override;
            virtual void        Open(const std::string& path, FileMode mode)    override;
            virtual bool        Seek(long offset, FileSeek mode)                override;
            virtual size_t      Read(BYTE* out, size_t len)                     override;
            virtual size_t      Write(BYTE* in, size_t len)                     override;
            virtual bool        Close(void)                                     override;
            virtual size_t      Tell(void)                                      override;
            virtual size_t      SizeBytes(void)                                 override;
            virtual size_t      SizeKBytes(void)                                override;
            virtual size_t      Position(void)                                  override;
            virtual FILE*       Handle(void)                                    override;

        private:
            std::string m_path;
            std::string m_name;
            std::string m_baseName;
            size_t      m_position;
            size_t      m_size;
            FILE*       m_handle;
        };

    }

}
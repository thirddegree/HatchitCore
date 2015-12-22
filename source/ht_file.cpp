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

#include <ht_file.h>

namespace Hatchit {

    namespace Core {

        File::File(void)
            : IFile()
        {
            m_position = 0;
            m_size = 0;
        }

        File::~File(void)
        {
            Close();
        }

        void File::Open(std::string path, FileMode mode)
        {
            m_path = os_path(path);
            m_name = GetName(m_path);
            m_baseName = GetName(m_path, false);

            switch (mode)
            {
                case FileMode::ReadBinary:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "rb");
                    #else
                        m_handle = fopen(m_path.c_str(), "rb");
                    #endif
                } break;

                case FileMode::ReadText:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "r");
                    #else
                        m_handle = fopen(m_path.c_str(), "r");
                    #endif
                } break;

                case FileMode::WriteBinary:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "wb");
                    #else
                        m_handle = fopen(m_path.c_str(), "wb");
                    #endif
                } break;

                case FileMode::WriteText:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "w");
                    #else
                        m_handle = fopen(m_path.c_str(), "w");
                    #endif
                } break;

                case FileMode::AppendBinary:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "ab");
                    #else
                        m_handle = fopen(m_path.c_str(), "ab");
                    #endif
                } break;

                case FileMode::AppendText:
                {
                    #ifdef HT_SYS_WINDOWS
                        fopen_s(&m_handle, m_path.c_str(), "a");
                    #else
                        m_handle = fopen(m_path.c_str(), "a");
                    #endif
                } break;

                default:
                    break;
            }

            if (!m_handle)
                throw FileException(m_path, errno);

        }

        bool File::Close(void)
        {
            int ret = 0;
            //Close file if handle is active
            if (m_handle)
            {
                fclose(m_handle);
                m_handle = nullptr;
            }

            return (ret <  0) ? false : true;
        }

        size_t File::Read(BYTE* out, size_t len)
        {
            size_t _len = 0;

            _len = fread(out, sizeof(BYTE), len, m_handle);

            int err = errno;
            if (err > 0)
                throw FileException(m_path, err);

            return _len;
        }

        size_t File::Write(BYTE* in, size_t len)
        {
            size_t _len = 0;

            _len = fwrite(in, sizeof(BYTE), len, m_handle);

            int err = errno;
            if (err > 0)
                throw FileException(m_path, err);

            return _len;
        }

        bool File::Seek(long pos, FileSeek mode)
        {
            switch (mode)
            {
                case FileSeek::Set:
                {
                    fseek(m_handle, pos, SEEK_SET);
                } break;

                case FileSeek::Current:
                {
                    fseek(m_handle, pos, SEEK_CUR);
                } break;

                case FileSeek::End:
                {
                    fseek(m_handle, pos, SEEK_END);
                } break;
            }

            m_position = Tell();

            int err = errno;
            if (err > 0) {
                throw FileException(m_path, err);
                return false;
            }

            return true;
        }

        size_t File::Tell(void)
        {
            return ftell(m_handle);
        }

        size_t File::Position(void)
        {
            return m_position;
        }

        size_t File::SizeBytes(void)
        {
            #ifdef HT_SYS_LINUX
                //Need to grab size from stat struct in order to allow for
                //files > 2GB in size
                struct stat st;
                stat(m_filePath.c_str(), &st);
                m_size = st.st_size;
            #else
                WIN32_FILE_ATTRIBUTE_DATA fad;
                if (!GetFileAttributesExA(m_path.c_str(), GetFileExInfoStandard, &fad))
                    return -1;

                LARGE_INTEGER size;
                size.HighPart = fad.nFileSizeHigh;
                size.LowPart = fad.nFileSizeLow;

                m_size = static_cast<size_t>(size.QuadPart);
            #endif

            return m_size;
        }

        size_t File::SizeKBytes(void)
        {
            return SizeBytes() / 1024;
        }

        std::string File::Name(void)
        {
            return m_name;
        }

        std::string File::Path(void)
        {
            return m_path;
        }

        std::string File::BaseName(void)
        {
            return m_baseName;
        }

        FILE* File::Handle(void)
        {
            return m_handle;
        }

        std::string File::GetExtension(const std::string& path, bool wd /* = true */)
        {
            std::string ext = "";
            size_t pos = path.rfind(".");
            if (pos != std::string::npos)
            {
                if (wd)
                    ext = path.substr(pos);
                else
                    ext = path.substr(pos + 1);
            }

            return ext;
        }

        std::string File::GetName(const std::string& path, bool we /* = true */)
        {
            std::string name = "";
            std::string _path = os_path(path);
            size_t pos = 0;
#ifdef HT_SYS_WINDOWS
            pos = _path.find_last_of('\\');
            if(pos != std::string::npos)
                _path.erase(0, pos + 1);
#else
            pos = _path.find_last_of('/');
            if (pos != std::string::npos)
                _path.erase(0, pos + 1);
#endif
            if (!we)
            {
                size_t extPos = _path.find_last_of(".");
                _path = _path.substr(0, extPos);
            }

            return _path;
        }
    }

}
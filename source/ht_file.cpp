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

#include <ht_file_exception.h>

#ifdef HT_SYS_LINUX
#include <sys/stat.h>
#endif

namespace Hatchit
{

    namespace Core
    {

        namespace
        {
            std::string GetExtension(const std::string& path, bool wd = true)
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

            std::string GetName(const std::string& path, bool we = true)
            {
                std::string name = "";
                std::string _path = os_path(path);
                size_t pos = 0;
#ifdef HT_SYS_WINDOWS
                pos = _path.find_last_of('\\');
                if (pos != std::string::npos)
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

        /**
        \fn File::File()
        \brief Creates empty file info

        Creates instance of File class with no information.  Class is not tied to any system file.
        **/
        File::File(void)
            : IFile(),
            m_position(0),
            m_size(0) {}

        /**
        \fn File::~File()
        \brief Closes file if file tied to it is open.

        Will close file opened with this instance if instance was used to open system file.
        **/
        File::~File(void)
        {
            Close();
        }

        /**
        \fn File::Open(const std::string& path, FileMode mode)
        \brief Opens file at given path using given file mode.

        Opens file and grabs handle to system file.  Will use one of
        the file modes given to determine how file may be used.
        **/
        void File::Open(const std::string& path, FileMode mode)
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
                        fopen_s(&m_handle, m_path.c_str(), "rt");
                    #else
                        m_handle = fopen(m_path.c_str(), "rt");
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
                        m_handle = fopen(m_path.c_str(), "w+");
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

        /**
        \fn File::Close()
        \brief Closes file and releases handle to system file.

        Will close an open file if one is held by this instance, and
        nullify its handle.
        **/
        bool File::Close(void)
        {
            int ret = 0;
            //Close file if handle is active
            if (m_handle)
            {
                ret = fclose(m_handle);
                m_handle = nullptr;
            }

            return (ret <  0) ? false : true;
        }

        /**
        \fn File::Read(BYTE* out, size_t len)
        \brief Fills \a out buffer with contents of file, up to size \a len

        Reads the contents of the file and places into buffer \a out.  Length
        of the buffer must be provided by \a len.

        /exception FileException The end of the file has already been reached, or
        if length given is 0.
        **/
        size_t File::Read(BYTE* out, size_t len)
        {
            size_t _len = 0;

            _len = fread(out, sizeof(BYTE), len, m_handle);

            if (_len == 0)
                throw FileException(m_path, errno);

            return _len;
        }

        /**
        \fn File::Write(BYTE* in, size_t len)
        \brief Fills system file with data from \a in, up to \a len bytes.

        Writes the contents of the buffer \a in into the file.  Length of 
        the buffer must be provided by \a len.

        /exception FileException The file system is not able to write
        the requested number of bytes into the file.
        **/
        size_t File::Write(BYTE* in, size_t len)
        {
            size_t _len = 0;

            _len = fwrite(in, sizeof(BYTE), len, m_handle);

            if(_len != len)
                throw FileException(m_path, errno);
                
            return _len;
        }

        /**
        \fn File::Seek(long pos, FileSeek mode)
        \brief Moves stream pointer to position \pos

        Moves stream pointer to position \a pos number of bytes
        from either the start of the file, or from the current position,
        depending on the FileSeek mode given.

        \return true if successful in moving to desired position, false otherwise

        \exception FileException The file stream could not move to the desired
        position.
        **/
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

        /**
        \fn File::Tell()
        \brief Gives current position of file stream

        This function gives the current position of the stream pointer in the file.
        for binary streams, this is the number of bytes from the beginning of the file.

        Further information can be found here: http://www.cplusplus.com/reference/cstdio/ftell/
        **/
        size_t File::Tell(void)
        {
            return ftell(m_handle);
        }

        /**
        \fn File::Position()
        \brief Gives the current position of the file stream

        This function gives the current position of the stream pointer in the file.
        For binary streams, this is the number of bytes from the beginning of the file.

        Further information can be found here: http://www.cplusplus.com/reference/cstdio/ftell/
        **/
        size_t File::Position(void)
        {
            return m_position;
        }

        /**
        \fn File::SizeBytes()
        \brief Gives the size of the system file in bytes.

        This function gives the size of the system file in bytes.

        \return size of the file in bytes, -1 if a failure occured in getting
        the file attributes.
        **/
        size_t File::SizeBytes(void)
        {
            #ifdef HT_SYS_LINUX
                //Need to grab size from stat struct in order to allow for
                //files > 2GB in size
                struct stat st;
                stat(m_path.c_str(), &st);
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

        /**
        \fn File::SizeKBytes()
        \brief Gives the size of the system file in kilobytes

        This function gives the size of the system file in kilobytes

        \return size of the file in bytes, -1 if a failure occured in getting
        the file attributes.
        **/
        size_t File::SizeKBytes(void)
        {
            return SizeBytes() / 1024;
        }

        /**
        \fn File::Name()
        \brief Gives the name of the system file

        This function returns the name of the system file.
        **/
        std::string File::Name(void)
        {
            return m_name;
        }

        /**
        \fn File::Path()
        \brief Gives the name of the path to the file.

        This function returns the path to the system file.
        **/
        std::string File::Path(void)
        {
            return m_path;
        }

        /**
        \fn File::BaseName()
        \brief Gives the base name of the system file.

        This function returns the base name of the system file.
        **/
        std::string File::BaseName(void)
        {
            return m_baseName;
        }

        /**
        \fn File::Handle()
        \brief Gives a file handle to the system file.

        This function returns a handle to the system file.
        **/
        FILE* File::Handle(void)
        {
            return m_handle;
        }
    }
}

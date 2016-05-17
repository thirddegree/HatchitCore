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

#include <ht_os.h> //os_path(std::string)
#include <ht_file_exception.h> //FileException
#include <cassert> //Assert statements

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
            //Assert that we do not have a file open before opening a new
            //file
            assert(!m_handle.is_open());

            m_path = os_path(path);
            m_name = GetName(m_path);
            m_baseName = GetName(m_path, false);
            m_position = 0;
            m_mode = static_cast<std::ios::openmode>(0);

            switch (mode)
            {
                case FileMode::ReadBinary:
                {
                    m_mode = std::ios::in | std::ios::binary;
                } break;

                case FileMode::ReadText:
                {
                    m_mode = std::ios::in;
                } break;

                case FileMode::WriteBinary:
                {
                    m_mode = std::ios::out | std::ios::binary;
                } break;

                case FileMode::WriteText:
                {
                    m_mode = std::ios::out;
                } break;

                case FileMode::AppendBinary:
                {
                    m_mode = std::ios::app | std::ios::binary;
                } break;

                case FileMode::AppendText:
                {
                    m_mode = std::ios::app;
                } break;

                default:
                    break;
            }

            m_handle.open(m_path, m_mode);

            if (!m_handle.is_open())
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
            if (m_handle.is_open())
            {
                m_handle.close();
                return true;
            }
            return false;
        }

        /**
        \fn File::Read(BYTE* out, size_t len)
        \brief Fills \a out buffer with contents of file, up to size \a len

        Reads the contents of the file and places into buffer \a out.  Length
        of the buffer must be provided by \a len.

        /exception FileException The end of the file has already been reached.
        **/
        size_t File::Read(BYTE* out, size_t len)
        {
            if (m_handle.eof())
            {
                throw FileException(m_path, EIO);
            }

            m_handle.read(reinterpret_cast<char*>(out), len);
            size_t count = m_handle.gcount();

            m_position += count;
            return count;
        }

        /**
        \fn File::Write(BYTE* in, size_t len)
        \brief Fills system file with data from \a in, up to \a len bytes.

        Writes the contents of the buffer \a in into the file.  Length of 
        the buffer must be provided by \a len.

        /exception FileException The file system is not able to write
        the requested number of bytes into the file.
        **/
        size_t File::Write(const BYTE* in, size_t len)
        {
            m_handle.write(reinterpret_cast<const char*>(in), len);
            
            if (m_handle.exceptions() & std::ios::badbit)
            {
                throw FileException(m_path, errno);
            }

            m_position += len;
            return len;
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
            // Get the seek mode
            std::ios::seekdir seekDir = static_cast<std::ios::seekdir>(0);
            switch (mode)
            {
                case FileSeek::Set:
                {
                    seekDir = std::ios::beg;
                } break;

                case FileSeek::Current:
                {
                    seekDir = std::ios::cur;
                } break;

                case FileSeek::End:
                {
                    seekDir = std::ios::end;
                } break;
            }

            // Call the correct seek method based on our open mode
            if ((m_mode & std::ios::out) || (m_mode & std::ios::app))
            {
                m_handle.seekp(pos, seekDir);
            }
            else
            {
                m_handle.seekg(pos, seekDir);
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
            if ((m_mode & std::ios::out) || (m_mode & std::ios::app))
            {
                return m_handle.tellp();
            }
            return m_handle.tellg();
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
        The base name of the file is the file name without the extension.
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
        std::fstream* File::Handle(void)
        {
            return &m_handle;
        }
    }
}

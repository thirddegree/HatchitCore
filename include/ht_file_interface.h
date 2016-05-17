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

#pragma once

#include <ht_platform.h> //HT_API
#include <string> //std::string typedef
#include <fstream> //std::fstream typedef
#include <cstddef> //size_t typedef
#include <ht_noncopy.h> //INonCopy

namespace Hatchit {

    namespace Core {

        /**
        \interface IFile
        \ingroup HatchitCore
        \brief An interface to describe system files.
        
        Interface describes the common functionality of files.
        
        **/
        class HT_API IFile : public INonCopy
        {
        public:
            /**
            \enum IFile::FileSeek
            \brief Mode in which to seek points in file

            Enum that describes the origin of which to offset pointer from.
            The following modes can be chosen:
            Set: Seeking is done relative to the beginning of the file
            Current: Seeking is done relative to the current position in the file
            End: Seeking is done relative to the end of the file.
            **/
            enum class FileSeek
            {
                Current,
                End,
                Set
            };

            /**
            \enum IFile::FileMode
            \brief Mode of which file is read from disk

            Enum that describes the method of which the file is read from disk
            to memory.

            The following modes can be chosen:
            ReadText: Open file for input operations.  File is interpreted as text.
            ReadBinary: Open file for input operations.  File is interpreted as binary.
            WriteText: Open an empty file for writing.  If the file exists, its contents are destroyed. (Text)
            WriteBinary: Open an empty file for writing.  If the file exists, its contents are destroyed. (Binary)
            AppendText: Opens file for writing at end of file. (Text)
            AppendBinary: Opens file for writing at end of file. (Binary)
            **/
            enum class FileMode
            {
                ReadText,
                ReadBinary,
                WriteText,
                WriteBinary,
                AppendText,
                AppendBinary
            };

            /**
            \fn IFile::~IFile()
            \brief Default destructor

            Default destructor
            **/
            virtual ~IFile() = default;

            /**
            \fn std::string IFile::Name()
            \brief Returns the name of the file

            Returns the name of the file, i.e. FileName.txt
            **/
            virtual std::string     Name(void) = 0;

            /**
            \fn std::string IFile::Path()
            \brief Returns the path to the file

            Returns the relative path to the file.
            Path includes file name appended to end.
            **/
            virtual std::string     Path(void) = 0;

            /**
            \fn std::string IFile::BaseName()
            \brief Returns the base name of the system file

            Returns the base name of the system file open.  Base
            name is the name of the file without the extension.
            **/
            virtual std::string     BaseName(void) = 0;

            /**
            \fn void IFile::Open(const std::string& path, FileMode mode)
            \brief Opens the file at the given path, using the given FileMode.

            Opens the file at the given relative path.  Then populates member data
            with information about the open file.
            **/
            virtual void            Open(const std::string& path, FileMode mode) = 0;

            /**
            \fn bool IFile::Seek(long offset, FileSeek mode)
            \brief Moves file stream pointer to requested offset relative to
            given mode

            Function moves the stream pointer to a new location, with an offset
            relative to the given FileSeek enum.
            \return Whether seeked position was found and moved to.
            **/
            virtual bool            Seek(long offset, FileSeek mode) = 0;

            /**
            \fn bool IFile::Close()
            \brief Closes current file and releases memory held from file.

            Function closes the currently open file and releases any memory
            from the file.  This function MUST be called before destruction
            of File objects.
            \return Whether file was successfully closed or not.
            **/
            virtual bool            Close(void) = 0;

            /**
            \fn size_t IFile::Read(BYTE* out, size_t length)
            \brief Reads contents of file into given byte buffer

            Function reads data from file (based on its current stream pointer
            position) and places data into given byte buffer, for a maximum of
            \a length number of bytes
            \return Number of bytes read into byte array.
            **/
            virtual size_t          Read(BYTE* out, size_t len) = 0;

            /**
            \fn size_t IFile::Write(BYTE* in, size_t len)
            \brief Writes contents of byte array into file output stream.

            Function writes contents of given byte array into the file's
            output stream. The function will write up to a maximum of
            \a len bytes.
            \return Number of bytes written to file.
            **/
            virtual size_t          Write(const BYTE* in, size_t len) = 0;

            /**
            \fn size_t IFile::Tell()
            \brief Gives current position of stream in file.

            Function returns the current position of the stream reader
            relative to the beginning of the file.

            \note Tell will be more or less arbitrary with text files,
            but can still be used to return to the same location with 
            IFile::Seek(long offset, FileSeek mode);
            **/
            virtual size_t          Tell(void) = 0;

            /**
            \fn size_t IFile::SizeBytes()
            \brief Gives size of file in bytes

            Gives size of file in bytes.
            **/
            virtual size_t          SizeBytes(void) = 0;

            /**
            \fn size_t IFile::SizeKBytes()
            \brief Gives size of file in Kilobytes

            Gives size of file in kilobytes
            **/
            virtual size_t          SizeKBytes(void) = 0;

            /**
            \fn size_t IFile::Position()
            \brief Returns position of stream pointer in file.

            Returns position of stream pointer in file (relative to beginning
            of file).
            **/
            virtual size_t          Position(void) = 0;

            /**
            \fn FILE* IFile::Handle()
            \brief Gives file pointer to opened file.

            Gives file pointer to opened file.
            **/
            virtual std::fstream*   Handle() = 0;
        };

    }

}
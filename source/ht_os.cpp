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

#include <ht_os.h>

#include <ht_platform.h> //HT_SYS_WINDOWS
#include <string> //std::string
#include <ht_string.h> //str_replaceAll()

#ifdef HT_SYS_WINDOWS
#include <direct.h> //_mkdir(const char*)
#include <fileapi.h>    //GetFileAttributesExA()
                        //INVALID_FILE_ATTRIBUTES

#include <WinBase.h>    //WIN32_FILE_ATTRIBUTE_DATA
                        //GetModuleFileNameA()

#include <winnt.h> //FILE_ATTRIBUTE_DIRECTORY
#endif

#ifdef HT_SYS_LINUX
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>
#endif

namespace Hatchit
{
    namespace Core
    {
        /*! \brief Function creates a directory on disk
        *
        *  Creates a directory on the file system with specified path
        *  @param path directory path
        */
        void os_mkdir(const std::string& path)
        {
            #ifdef HT_SYS_WINDOWS
                _mkdir(path.c_str());
            #elif defined(HT_SYS_LINUX)
                mkdir(path.c_str(), S_IRWXU);
            #endif
        }

        /*! \brief Function checks is specified path is a directory
        *
        *  Returns true or false is specified path is a directory
        *  @param path directory path
        */
        bool os_isdir(const std::string& path)
        {
            //convert path
            std::string _path = os_path(path);
            #ifdef HT_SYS_WINDOWS
                WIN32_FILE_ATTRIBUTE_DATA info;
                GetFileAttributesExA(_path.c_str(), GetFileExInfoStandard, &info);
                return (info.dwFileAttributes != INVALID_FILE_ATTRIBUTES &&
                        (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
            #elif defined(HT_SYS_LINUX)
                struct stat info;
                stat(_path.c_str(), &info);
                return S_ISDIR(info.st_mode);
            #endif

            return false;
        }

        /*! \brief Function returns os standard path
        *
        *  Returns specified path with correct path delimeters
        *  @param path the system path
        */
        std::string os_path(const std::string& path)
        {
            std::string temp = path;

            #ifdef HT_SYS_WINDOWS
                str_replaceAll(temp, "/", "\\");
            #else
                str_replaceAll(temp, "\\", "/");
            #endif

            return temp;
        }

        /*! \brief Function returns the parent directory of a path
        *
        *  @param path system path
        *  @param wt   should include trailing slash
        */
        std::string os_dir(const std::string& path, bool wt)
        {
            if(path.empty())
                return "";

            std::string dir = "";

            //remove trailing slash for now
            dir = path.substr(0, path.size() - 1);

            size_t back_slash = 0;
            char c_slash;
            #ifdef HT_SYS_WINDOWS
                c_slash = '\\';
            #else
                c_slash = '/';
            #endif
            back_slash = dir.find_last_of(c_slash);
            if (back_slash != std::string::npos)
                dir = dir.substr(0, back_slash);
            if (wt)
                dir += c_slash;

            return dir;
        }

        /*! \brief Function returns the current executable directory
        *
        */
        std::string os_exec_dir()
        {
            #ifdef HT_SYS_WINDOWS
                char path[MAX_PATH];
                GetModuleFileNameA(NULL, path, MAX_PATH);
                return os_dir(path);
            #else
                char arg1[20];
                char exepath[PATH_MAX + 1] = {0};
                sprintf( arg1, "/proc/%d/exe", getpid() );
                readlink( arg1, exepath, 1024 );
                return os_dir(exepath);
            #endif

            return "";
        }

        /**
         * \brief Function returns the name of current executable
         */
        std::string os_exec_name()
        {
            std::string _name;

            #ifdef HT_SYS_WINDOWS

            #else
                char arg1[20];
                char exepath[PATH_MAX + 1] = {0};
                sprintf(arg1, "/proc/%d/exe", getpid());
                readlink(arg1, exepath, 1024);

                _name = exepath;
                size_t pos = 0;
                pos = _name.find_last_of('/');
                if (pos != std::string::npos)
                    _name.erase(0, pos + 1);

            #endif

            return _name;
        }

        /*! \brief Function returns the path delimeter character
        *
        */
        char os_path_delimeter()
        {
            char delimeter;
#ifdef HT_SYS_WINDOWS
            delimeter = '\\';
#else
            delimeter = '/';
#endif
            return delimeter;
        }
    }

}

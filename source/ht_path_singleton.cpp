/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 ThirdDegree
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

#include <ht_path_singleton.h>

#include <string> //std::string typedef
#include <ht_inisettings.h> //INIReader
#include <ht_os.h> //os_path stuff

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn void Path::Initialize(INIReader& settings)
        \brief Finds common game directories and stores their paths

        Initializes Path object with strings to the common game directories.
        **/
        void Path::Initialize(INISettings& settings)
        {
            Path& _instance = Path::instance();

            std::string _AssetPath = os_path(settings.GetValue("PATHS", "sAssetPath", os_exec_dir() + "Assets/"));
            if (_AssetPath.back() != os_path_delimeter())
                _AssetPath += os_path_delimeter();

            _instance.m_paths.insert(std::make_pair(Directory::Assets, _AssetPath));
            _instance.m_paths.insert(std::make_pair(Directory::Models, _AssetPath + os_path("Models/")));
            _instance.m_paths.insert(std::make_pair(Directory::Materials, _AssetPath + os_path("Materials/")));
            _instance.m_paths.insert(std::make_pair(Directory::Textures, _AssetPath + os_path("Textures/")));
            _instance.m_paths.insert(std::make_pair(Directory::Pipelines, _AssetPath + os_path("Pipelines/")));
            _instance.m_paths.insert(std::make_pair(Directory::RenderPasses, _AssetPath + os_path("RenderPasses/")));
            _instance.m_paths.insert(std::make_pair(Directory::RenderTargets, _AssetPath + os_path("RenderTargets/")));
            _instance.m_paths.insert(std::make_pair(Directory::Samplers, _AssetPath + os_path("Samplers/")));
            _instance.m_paths.insert(std::make_pair(Directory::Scenes, _AssetPath + os_path("Scenes/")));
            _instance.m_paths.insert(std::make_pair(Directory::Scripts, _AssetPath + os_path("Scripts/")));
            _instance.m_paths.insert(std::make_pair(Directory::Shaders, _AssetPath + os_path("Shaders/")));
        }

        /**
        \fn void Path::DeInitialize()
        \brief Deinitializes path variable
        **/
        void Path::DeInitialize()
        {

        }

        /**
        \fn std::string Path::Value(Directory directory)
        \brief Provides string representing path to given directory.
        **/
        std::string Path::Value(Directory directory)
        {
            Path& _instance = Path::instance();

            return _instance.m_paths[directory];
        }
    }
}
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
#include <ht_os.h>

namespace Hatchit
{
    namespace Core
    {
        void Path::Initialize(Hatchit::Core::INIReader* settings)
        {
            Path& _instance = Path::instance();

            std::string _AssetPath = os_path(settings->GetValue("PATHS", "sAssetPath", os_exec_dir() + "Assets/"));
            if (_AssetPath.back() != os_path_delimeter())
                _AssetPath += os_path_delimeter();

            _instance.m_paths.insert(std::make_pair(Directory::Assets, _AssetPath));
            _instance.m_paths.insert(std::make_pair(Directory::Models, _AssetPath + os_path("Models/")));
            _instance.m_paths.insert(std::make_pair(Directory::Textures, _AssetPath + os_path("Textures/")));
            _instance.m_paths.insert(std::make_pair(Directory::Pipelines, _AssetPath + os_path("Pipelines/")));
            _instance.m_paths.insert(std::make_pair(Directory::Scenes, _AssetPath + os_path("Scenes/")));
            _instance.m_paths.insert(std::make_pair(Directory::Scripts, _AssetPath + os_path("Scripts/")));
            _instance.m_paths.insert(std::make_pair(Directory::Shaders, _AssetPath + os_path("Shaders/")));
        }

        void Path::DeInitialize()
        {

        }

        std::string Path::Value(Directory directory)
        {
            Path& _instance = Path::instance();

            return _instance.m_paths[directory];
        }
    }
}
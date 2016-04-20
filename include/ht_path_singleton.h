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

#pragma once

#include <ht_platform.h> //HT_API
#include <ht_singleton.h> //Singleton<T>
#include <map> //std::map

//Forward declarations
namespace Hatchit
{
    namespace Core
    {
        class INIReader;
    }
}

namespace Hatchit
{
    namespace Core
    {
        /**
        \class Path
        \ingroup HatchitCore
        \brief Describes file path to common game directories.

        Class provides paths to common game directories for assets.
        **/
        class HT_API Path : public Singleton<Path>
        {
        public:

            /**
            \enum Path::Directory
            \ingroup HatchitCore
            \brief Common game directories used by engine

            This enum lists the common game directories used by Hatchit.
            This enum may be used to gain a string path to the directory.
            **/
            enum class Directory
            {
                Assets,
                Models,
                Materials,
                Pipelines,
                RenderPasses,
                RenderTargets,
                Textures,
                Samplers,
                Shaders,
                Scenes,
                Scripts
            };

            static void Initialize(INIReader& settings);
            
            static void DeInitialize();

            static std::string Value(Directory directory);

        private:
            std::map<Directory, std::string> m_paths;
        };
    }
}
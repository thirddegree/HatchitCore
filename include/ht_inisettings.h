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

//Header includes
#include <ht_platform.h> //HT_API
#include <map> //std::map
#include <vector> //std::vector
#include <utility> //std::pair
#include <string> //std::string

//Inline includes
#include <algorithm> //std::find, std::transform
//#include <string> //std::stoi
#include <stdexcept> //std::invalid_argument

//Forward Declarations
namespace Hatchit
{
    namespace Core
    {
        class File;
    }
}

namespace Hatchit
{
    namespace Core
    {
        class HT_API INISettings
        {
            using ValuePairList = std::vector<std::pair<std::string, std::string>>;

        public:
            INISettings();

            void Load(File& file);
            void Write(File& file);

            template <typename T>
            T GetValue(const std::string& section, const std::string& name);
        
            template <typename T>
            void SetValue(const std::string& section, const std::string& name, T value);

        private:
            std::map<std::string, ValuePairList> m_values;
        
            std::string             Get(const std::string& section, const std::string& name);
            static char*            StreamReader(char* str, int len, void* stream);
            static int              ValueHandler(void* user, const char* section, const char* name, const char* value);
        };
    }
}

#include <ht_inisettings.inl>

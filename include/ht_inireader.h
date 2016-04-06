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

#include <ht_platform.h>
#include <ht_file.h>
#include <ht_ini_exception.h>
#include <ini.h>
#include <map>
#include <algorithm>

namespace Hatchit {

    namespace Core {

        class HT_API INIReader
        {
        public:
            INIReader(void);

            void Load(File* file);

            bool Empty();

            template <typename T>
            T GetValue(std::string section, std::string name, T default_val);

        private:
            int                                 m_error;
            std::map<std::string, std::string>  m_values;

            std::string Get(std::string section, std::string name);
            static std::string      MakeKey(std::string section, std::string name);
            static int              ValueHandler(void* user, const char* section, const char* name, const char* value);
        };

        template <>
        inline std::string INIReader::GetValue(std::string section, std::string name, std::string default_val)
        {
            std::string value_str = Get(section, name);

            if (value_str.empty())
                return default_val;
            else
                return value_str;
        }

        template <>
        inline bool INIReader::GetValue(std::string section, std::string name, bool default_val)
        {
            std::string value_str = Get(section, name);

            std::transform(value_str.begin(), value_str.end(), value_str.begin(), ::tolower);
            if (value_str == "true" || value_str == "yes" || value_str == "on" || value_str == "1")
                return true;
            else if (value_str == "false" || value_str == "no" || value_str == "off" || value_str == "0")
                return false;
            else
                return default_val;
        }

        template <>
        inline int INIReader::GetValue(std::string section, std::string name, int default_val)
        {
            std::string value_str = Get(section, name);

            const char* value = value_str.c_str();

            int _val = std::atoi(value);

            return _val != 0 ? _val : default_val;
        }

        template <>
        inline double INIReader::GetValue(std::string section, std::string name, double default_val)
        {
            std::string value_str = Get(section, name);

            const char* value = value_str.c_str();

            double _val = std::atof(value);

            return _val != 0.0 ? _val : default_val;
        }

        template <>
        inline float INIReader::GetValue(std::string section, std::string name, float default_val)
        {
            return static_cast<float>(INIReader::GetValue<double>(section, name, default_val));
        }
    }

}
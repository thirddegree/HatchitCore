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

#include <ht_inisettings.h>

namespace Hatchit
{
    namespace Core
    {
        template <>
        inline void INISettings::SetValue(const std::string& section, const std::string& name, int value)
        {
            ValuePairList& list = m_values[section];

           
            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = value;
        }

        template <>
        inline void INISettings::SetValue(const std::string& section, const std::string& name, bool value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = value;
        }

        template <>
        inline void INISettings::SetValue(const std::string& section, const std::string& name, float value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = static_cast<char>(value);
        }

        template <>
        inline void INISettings::SetValue(const std::string& section, const std::string& name, std::string value)
        {
            std::string val = value;
            auto it = m_values.find(section);
            if (it != m_values.end())
            {
                ValuePairList& v = it->second;
                auto loc = std::find(v.begin(), v.end(), std::make_pair(name, val));
                if (loc == v.end())
                    v.push_back(std::make_pair(name, val));
                else
                    loc->second = value;
            }
        }

        template <>
        inline void INISettings::SetValue(const std::string& section, const std::string& name, double value)
        {
            std::string val = std::to_string(value);
            auto it = m_values.find(section);
            if (it != m_values.end())
            {
                ValuePairList& v = it->second;
                auto loc = std::find(v.begin(), v.end(), std::make_pair(name, val));
                if (loc == v.end())
                    v.push_back(std::make_pair(name, val));
                else
                    loc->second = static_cast<char>(value);
            }
             
        }


        template <>
        inline std::string INISettings::GetValue(const std::string& section, const std::string& name, std::string default_val)
        {
            std::string value_str = Get(section, name);

            if (value_str.empty())
                return default_val;
            else
                return value_str;
        }

        template <>
        inline bool INISettings::GetValue(const std::string& section, const std::string& name, bool default_val)
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
        inline int INISettings::GetValue(const std::string& section, const std::string& name, int default_val)
        {
            std::string value_str = Get(section, name);

            const char* value = value_str.c_str();

            int _val = std::atoi(value);

            return _val != 0 ? _val : default_val;
        }

        template <>
        inline double INISettings::GetValue(const std::string& section, const std::string& name, double default_val)
        {
            std::string value_str = Get(section, name);

            const char* value = value_str.c_str();

            double _val = std::atof(value);

            return _val != 0.0 ? _val : default_val;
        }

        template <>
        inline float INISettings::GetValue(const std::string& section, const std::string& name, float default_val)
        {
            return static_cast<float>(INISettings::GetValue<double>(section, name, default_val));
        }
    }
}

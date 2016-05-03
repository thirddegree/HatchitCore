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

#include <ht_inisettings.h>

namespace Hatchit
{
    namespace Core
    {
        /**
        \fn void INISettings::SetValue<int>(const std::string& section, const std::string& name, int value)
        \brief Sets the value for a given key \a name in a given \a section

        Sets the value for a given key \a name in a given \a section.
        If the key already exists, the previous value will be overwritten.
        If the key did not already exist, a new key-value pair will be created.
        **/
        template <>
        inline void INISettings::SetValue<int>(
            const std::string& section, 
            const std::string& name, 
            int value)
        {
            ValuePairList& list = m_values[section];

           
            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = std::move(value);
        }

        /**
        \fn void INISettings::SetValue<bool>(const std::string& section, const std::string& name, bool value)
        \brief Sets the value for a given key \a name in a given \a section

        Sets the value for a given key \a name in a given \a section.
        If the key already exists, the previous value will be overwritten.
        If the key did not already exist, a new key-value pair will be created.
        **/
        template <>
        inline void INISettings::SetValue<bool>(
            const std::string& section, 
            const std::string& name, 
            bool value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = std::move(value);
        }

        /**
        \fn void INISettings::SetValue<float>(const std::string& section, const std::string& name, float value)
        \brief Sets the value for a given key \a name in a given \a section

        Sets the value for a given key \a name in a given \a section.
        If the key already exists, the previous value will be overwritten.
        If the key did not already exist, a new key-value pair will be created.
        **/
        template <>
        inline void INISettings::SetValue<float>(
            const std::string& section, 
            const std::string& name, 
            float value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);
            auto it = std::find(list.begin(), list.end(), std::make_pair(name, val));
            if (it == list.end())
                list.push_back(std::make_pair(name, val));
            else
                it->second = static_cast<char>(value);
        }

        /**
        \fn void INISettings::SetValue<std::string>(const std::string& section, const std::string& name, std::string value)
        \brief Sets the value for a given key \a name in a given \a section

        Sets the value for a given key \a name in a given \a section.
        If the key already exists, the previous value will be overwritten.
        If the key did not already exist, a new key-value pair will be created.
        **/
        template <>
        inline void INISettings::SetValue<std::string>(
            const std::string& section, 
            const std::string& name, 
            std::string value)
        {
            auto it = m_values.find(section);
            if (it != m_values.end())
            {
                ValuePairList& v = it->second;
                auto loc = std::find(v.begin(), v.end(), std::make_pair(name, value));
                if (loc == v.end())
                    v.push_back(std::make_pair(name, value));
                else
                    loc->second = std::move(value);
            }
        }

        /**
        \fn void INISettings::SetValue<double>(const std::string& section, const std::string& name, double value)
        \brief Sets the value for a given key \a name in a given \a section

        Sets the value for a given key \a name in a given \a section.
        If the key already exists, the previous value will be overwritten.
        If the key did not already exist, a new key-value pair will be created.
        **/
        template <>
        inline void INISettings::SetValue<double>(
            const std::string& section, 
            const std::string& name, 
            double value)
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

        /**
        \fn std::string INISettings::GetValue<std::string>(const std::string& section, const std::string& name)
        \brief Gets value for given key \a name in given \a section.

        Gets value for given key \a name in given section.  If a key is not
        found for the given section, an std::invalid_argument will be thrown.
        **/
        template <>
        inline std::string INISettings::GetValue<std::string>(
            const std::string& section, 
            const std::string& name)
        {
            std::string value_str = Get(section, name);

            if (value_str.empty())
                throw std::invalid_argument("Invalid argument for " + name + " in section " + section);
            else
                return value_str;
        }

        /**
        \fn bool INISettings::GetValue<bool>(const std::string& section, const std::string& name)
        \brief Gets value for given key \a name in given \a section.

        Gets value for given key \a name in given section.  If a key is not
        found for the given section, an std::invalid_argument will be thrown.
        If the value for given name cannot be converted into a bool,
        an std::invalid_argument will be thrown.
        **/
        template <>
        inline bool INISettings::GetValue<bool>(
            const std::string& section, 
            const std::string& name)
        {
            std::string value_str = Get(section, name);

            std::transform(value_str.begin(), value_str.end(), value_str.begin(), ::tolower);
            if (value_str == "true" || value_str == "yes" || value_str == "on" || value_str == "1")
                return true;
            else if (value_str == "false" || value_str == "no" || value_str == "off" || value_str == "0")
                return false;
            else
                throw std::invalid_argument("Invalid argument for " + name + " in section " + section);
        }

        /**
        \fn int INISettings::GetValue<int>(const std::string& section, const std::string& name)
        \brief Gets value for given key \a name in given \a section.

        Gets value for given key \a name in given section.  If a key is not
        found for the given section, an std::invalid_argument will be thrown.
        If the value for given name cannot be converted into an int,
        an std::invalid_argument will be thrown.
        **/
        template <>
        inline int INISettings::GetValue<int>(
            const std::string& section, 
            const std::string& name)
        {
            try
            {
                return std::stoi(Get(section, name));
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid argument for " + name + " in section " + section);
            }
            
        }

        /**
        \fn double INISettings::GetValue<double>(const std::string& section, const std::string& name)
        \brief Gets value for given key \a name in given \a section.

        Gets value for given key \a name in given section.  If a key is not
        found for the given section, an std::invalid_argument will be thrown.
        If the value for given name cannot be converted into a double,
        an std::invalid_argument will be thrown.
        **/
        template <>
        inline double INISettings::GetValue<double>(
            const std::string& section, 
            const std::string& name)
        {
            try
            {
                return std::stod(Get(section, name));
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid argument for " + name + " in section " + section);
            }
        }

        /**
        \fn float INISettings::GetValue<float>(const std::string& section, const std::string& name)
        \brief Gets value for given key \a name in given \a section.

        Gets value for given key \a name in given section.  If a key is not
        found for the given section, an std::invalid_argument will be thrown.
        If the value for given name cannot be converted into a float,
        an std::invalid_argument will be thrown.
        **/
        template <>
        inline float INISettings::GetValue<float>(
            const std::string& section, 
            const std::string& name)
        {
            try
            {
                return std::stof(Get(section, name));
            }
            catch (const std::invalid_argument&)
            {
                throw std::invalid_argument("Invalid argument for " + name + " in section " + section);
            }
            
        }
    }
}

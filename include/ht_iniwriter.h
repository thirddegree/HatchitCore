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

#include <ht_platform.h>
#include <ht_string.h>
#include <ht_file.h>
#include <map>
#include <vector>

namespace Hatchit {

    namespace Core {

        class HT_API INIWriter
        {
            typedef std::vector<std::pair<std::string, std::string> > ValuePairList;
        public:
            INIWriter(void);

            void Write(File* file);

            template <typename T>
            void SetValue(std::string section, std::string name, T value);

        private:
            std::map<std::string, ValuePairList> m_values;
        };

        template <>
        inline void INIWriter::SetValue(std::string section, std::string name, int value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);
            
            list.push_back(std::make_pair(name, val));
        }

        template <>
        inline void INIWriter::SetValue(std::string section, std::string name, bool value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);

            list.push_back(std::make_pair(name, val));
        }
        
        template <>
        inline void INIWriter::SetValue(std::string section, std::string name, float value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);

            list.push_back(std::make_pair(name, val));
        }

        template <>
        inline void INIWriter::SetValue(std::string section, std::string name, double value)
        {
            ValuePairList& list = m_values[section];

            std::string val = std::to_string(value);

            list.push_back(std::make_pair(name, val));
        }
    }

}
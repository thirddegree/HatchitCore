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

#include <ht_iniwriter.h>

namespace Hatchit {

    namespace Core {

        INIWriter::INIWriter()
        {

        }


        void INIWriter::Write(File* file)
        {
            if (!file)
                return;

            for (auto& key : m_values)
            {
                //write section
                std::string section = "[" + key.first + "]\n";
                file->Write((BYTE*)section.c_str(), section.size());

                ValuePairList _map = key.second;
                for (size_t i = 0; i < _map.size(); i++)
                {
                    std::string name = _map[i].first;
                    name += "=" + _map[i].second;
                    name += "\n";

                    file->Write((BYTE*)name.c_str(), name.size());
                }
            }
        }
    }

}
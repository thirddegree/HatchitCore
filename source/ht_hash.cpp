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

#include <ht_hash.h>

namespace Hatchit
{
    namespace Core
    {
        namespace Hash
        {
            uint64_t FNV1A(const std::string& text)
            {
                uint64_t offset_basis = 0xCBF29CE484222325;
                uint64_t prime = 0x100000001B3;

                uint64_t hash = offset_basis;
                for (uint64_t index = 0; index < text.size(); ++index)
                {
                    hash *= prime;
                    hash ^= text[index];
                }

                return hash;
            }

            uint64_t FNV1A(const std::wstring& text)
            {
                uint64_t offset_basis = 0xCBF29CE484222325;
                uint64_t prime = 0x100000001B3;

                uint64_t hash = offset_basis;
                for (uint64_t index = 0; index < text.size(); ++index)
                {
                    hash *= prime;
                    hash ^= text[index];
                }

                return hash;
            }
        }

    }
}
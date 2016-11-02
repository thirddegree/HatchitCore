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
        uint64_t FNV1A_Hash(const std::wstring& text)
        {
            // This is adapted from the 64-bit version of the FNV-1a hashing algorithm
            // Source:  http://www.isthe.com/chongo/tech/comp/fnv/
            // License: Public Domain

            uint64_t hash = 0;
            for (uint64_t index = 0; index < text.size(); ++index)
            {
                hash ^= static_cast<uint64_t>(text[index]);

                // The algorithm differs on the next part, so if we're compiling using
                // GCC, then let's just use their optimization
#if defined(__GNUC__)
                hash += (hash << 1) + (hash << 4) + (hash << 5) +
                        (hash << 7) + (hash << 8) + (hash << 40);
#else
                hash *= 0x100000001b3ULL;
#endif
            }

            return hash;
        }
    }
}
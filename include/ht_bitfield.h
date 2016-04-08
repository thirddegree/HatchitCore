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

#include <type_traits>

namespace Hatchit
{
    namespace Core
    {
        class BitFlag
        {
            int i;
        public:
            constexpr inline BitFlag(long pI) : i(static_cast<int>(pI)) {}
            constexpr inline BitFlag(unsigned long pI) : i(static_cast<int>(static_cast<long>(pI))) {}
            constexpr inline BitFlag(int pI) : i(pI) {}
            constexpr inline BitFlag(unsigned int pI) : i(static_cast<int>(pI)) {}
            constexpr inline BitFlag(short pS) : i(static_cast<int>(pS)) {}
            constexpr inline BitFlag(unsigned short pS) : i(static_cast<int>(static_cast<short>(pS))) {}

            constexpr inline operator int() const { return i; }
            constexpr inline operator unsigned int() const { return static_cast<unsigned int>(i); }
        };

        template<typename Enum>
        class BitField
        {
            static_assert(sizeof(Enum) <= sizeof(int), "Underlying type of BitField is size of int.  Enums larger than an int will cause overflow.");

        public:
            using  BitfieldType = typename std::conditional<std::is_unsigned<Enum>::value, unsigned int, signed int>::type;
            using EnumType = Enum;

        private:
            BitfieldType i;

        public:

            constexpr inline BitField(EnumType e) : i(BitfieldType(e)) {}
            constexpr inline BitField(BitfieldType = 0) : i(0) {}
            constexpr inline BitField(BitFlag b) : i(b) {}

            inline BitField& operator&=(int mask) { i &= mask; return *this; }
            inline BitField& operator&=(unsigned int mask) { i &= mask; return *this; }
            inline BitField& operator&=(Enum mask) { i &= BitfieldType(mask); return *this; }
            inline BitField& operator&=(BitField b) { i &= b.i; return *this; }
            inline BitField& operator|=(int mask) { i |= mask; return *this; }
            inline BitField& operator|=(unsigned int mask) { i |= mask; return *this; }
            inline BitField& operator|=(Enum mask) { i |= BitfieldType(mask); return *this; }
            inline BitField& operator|=(BitField b) { i |= b.i; return *this; }
            inline BitField& operator^=(int mask) { i ^= mask; return *this; }
            inline BitField& operator^=(unsigned int mask) { i ^= mask; return *this; }
            inline BitField& operator^=(Enum mask) { i ^= BitfieldType(mask); return *this; }
            inline BitField& operator^=(BitField b) { i ^= b.i; return *this; }

            constexpr inline operator BitfieldType() const { return i; }

            constexpr inline BitField operator&(int mask) const { return BitField(BitFlag(i & mask)); }
            constexpr inline BitField operator&(unsigned int mask) const { return BitField(BitFlag(i & mask)); }
            constexpr inline BitField operator&(Enum mask) const { return BitField(BitFlag(i & BitfieldType(mask))); }
            constexpr inline BitField operator&(BitField mask) const { return BitField(BitFlag(i & mask.i)); }
            constexpr inline BitField operator|(int mask) const { return BitField(BitFlag(i | mask)); }
            constexpr inline BitField operator|(unsigned int mask) const { return BitField(BitFlag(i | mask)); }
            constexpr inline BitField operator|(Enum mask) const { return BitField(BitFlag(i | BitfieldType(mask))); }
            constexpr inline BitField operator|(BitField mask) const { return BitField(BitFlag(i | mask.i)); }
            constexpr inline BitField operator^(int mask) const { return BitField(BitFlag(i ^ mask)); }
            constexpr inline BitField operator^(unsigned int mask) const { return BitField(BitFlag(i ^ mask)); }
            constexpr inline BitField operator^(Enum mask) const { return BitField(BitFlag(i ^ BitfieldType(mask))); }
            constexpr inline BitField operator^(BitField mask) const { return BitField(BitFlag(i ^ mask.i)); }

            constexpr inline BitField operator~() const { return BitField(BitFlag(~i)); }

            constexpr inline bool operator!() const { return !i; }

            constexpr inline bool TestFlag(Enum flag) const { return (i & BitfieldType(flag)) == BitfieldType(flag) && (BitfieldType(flag) != 0 || i == BitfieldType(flag)); }
        };
    }
}
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

/**
 * \file ht_bitfield.h
 * \brief BitField class definition
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains definition for BitField class
 */


#include <type_traits>

namespace Hatchit
{
    namespace Core
    {
        /**
        * \class BitFlag
        * \brief A class that represents a single bit flag
        *
        * Class stores a single bit flag that may be used for testing flags
        * in the BitField class.
        * 
        */
        class BitFlag
        {
        public:
            
            constexpr BitFlag(long pI);
            constexpr BitFlag(unsigned long pI);
            constexpr BitFlag(int pI);
            constexpr BitFlag(unsigned int pI);
            constexpr BitFlag(short pS);
            constexpr BitFlag(unsigned short pS);

            //Operators
            constexpr operator int() const;
            constexpr operator unsigned int() const;

        private:
            int i;
        };

        /**
        * \class BitField
        * \brief A class that represents an array of bitflags for a given enum
        *
        * Stores marked bits for a given enum in a bit array, or bit field.
        */
        template<typename Enum>
        class BitField
        {
            static_assert(sizeof(Enum) <= sizeof(int), "Underlying type of BitField is size of int.  Enums larger than an int will cause overflow.");

        public:

            /**
            * \typedef BitField<Enum>::BitfieldType
            * \brief Internal type used in bitfield
            *
            * The internal type that is used in the bitfield, determined based
            * on the internal type of the Enum.  If the enum is unsigned, then
            * the internal type is also unsigned.  Will always be size of int.
            **/
            using BitfieldType = typename std::conditional<std::is_unsigned<Enum>::value, unsigned int, signed int>::type;

            /**
            * \typedef BitField<Enum>::EnumType
            * \brief Enum given from template parameter
            *
            * The enum given from the template parameter.
            **/
            using EnumType = Enum;

            constexpr BitField(EnumType e);
            constexpr BitField(BitfieldType val = 0);
            constexpr BitField(BitFlag b);


            constexpr operator BitfieldType() const;

            BitField& operator&=(int mask);
            BitField& operator&=(unsigned int mask);
            BitField& operator&=(Enum mask);
            BitField& operator&=(BitField mask);
            BitField& operator|=(int mask);
            BitField& operator|=(unsigned int mask);
            BitField& operator|=(Enum mask);
            BitField& operator|=(BitField mask);
            BitField& operator^=(int mask);
            BitField& operator^=(unsigned int mask);
            BitField& operator^=(Enum mask);
            BitField& operator^=(BitField mask);

            constexpr BitField operator&(int mask) const;
            constexpr BitField operator&(unsigned int mask) const;
            constexpr BitField operator&(Enum mask) const;
            constexpr BitField operator&(BitField mask) const;
            constexpr BitField operator|(int mask) const;
            constexpr BitField operator|(unsigned int mask) const;
            constexpr BitField operator|(Enum mask) const;
            constexpr BitField operator|(BitField mask) const;
            constexpr BitField operator^(int mask) const;
            constexpr BitField operator^(unsigned int mask) const;
            constexpr BitField operator^(Enum mask) const;
            constexpr BitField operator^(BitField mask) const;

            constexpr BitField operator~() const;

            constexpr bool operator!() const;

            constexpr bool TestFlag(Enum flag) const;

        private:
            BitfieldType i;
        };
    }
}

#include <ht_bitfield.inl>
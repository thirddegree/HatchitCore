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

#include <ht_bitfield.h>

namespace Hatchit
{
    namespace Core
    {
        //////////////////////////////////////////////////////////////////////
        //// BITFLAG IMPLEMENTATION
        //////////////////////////////////////////////////////////////////////

        /**
        \fn BitFlag::BitFlag(long)
        \brief Creates Bitflag from long

        Creates a bitflag from a long.  Long will be truncated to size of int.
        \return A bitflag with bits marked from those marked in long.
        */
        constexpr inline BitFlag::BitFlag(long pI) : i(static_cast<int>(pI)) {}

        /**
        \fn BitFlag::BitFlag(unsigned long)
        \brief Creates Bitflag from long

        Creates a bitflag from an unsigned long.  Long will be truncated to size of int.
        \return A bitflag with bits marked from those marked in long.
        */
        constexpr inline BitFlag::BitFlag(unsigned long pI) : i(static_cast<int>(static_cast<long>(pI))) {}

        /**
        \fn BitFlag::BitFlag(int)
        \brief Creates Bitflag from int

        Creates a bitflag from an int.
        \return A bitflag with bits marked from those marked in int.
        */
        constexpr inline BitFlag::BitFlag(int pI) : i(pI) {}

        /**
        \fn BitFlag::BitFlag(unsigned int)
        \brief Creates Bitflag from int

        Creates a bitflag from an int.
        \return A bitflag with bits marked from those marked in int.
        */
        constexpr inline BitFlag::BitFlag(unsigned int pI) : i(static_cast<int>(pI)) {}

        /**
        \fn BitFlag::BitFlag(short)
        \brief Creates Bitflag from short

        Creates a bitflag from a short.
        \return A bitflag with bits marked from those marked in short.
        */
        constexpr inline BitFlag::BitFlag(short pS) : i(static_cast<int>(pS)) {}

        /**
        \fn BitFlag::BitFlag(unsigned short)
        \brief Creates Bitflag from short

        Creates a bitflag from a short.
        \return A bitflag with bits marked from those marked in short.
        */
        constexpr inline BitFlag::BitFlag(unsigned short pS) : i(static_cast<int>(static_cast<short>(pS))) {}


        /**
        \fn BitFlag::operator int()
        \brief Returns int representation of bitflag.

        Returns internal int member inside bitflag to represent
        bit flag.
        **/
        constexpr inline BitFlag::operator int() const { return i; }

        /**
        \fn BitFlag::operator unsigned int()
        \brief Returns unsigned int representation of bitflag.

        Returns internal int member inside bitflag to represent
        bit flag (cast to unsigned int).
        **/
        constexpr inline BitFlag::operator unsigned int() const { return static_cast<unsigned int>(i); }

        //////////////////////////////////////////////////////////////////////
        //// BITFIELD IMPLEMENTATION
        //////////////////////////////////////////////////////////////////////

        /**
        \fn BitField<Enum>::BitField(EnumType)
        \brief Creates bitfield with single bit marked.

        Creates a bitfield with a single bit marked from the
        enum value given.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum>::BitField(EnumType e) : i(BitfieldType(e)) {}

        /**
        \fn BitField<Enum>::BitField(BitFieldType)
        \brief Creates bitfield with given value to initialize bitfield.

        Creates bitfield with given value to initialize bits.  If no value
        is given, will initialize bits to zero.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum>::BitField(BitfieldType val) : i(val) {}

        /**
        \fn BitField<Enum>::BitField(BitFlag)
        \brief Creates bitfield with given bitflag to initialize bitfield.

        Creates bitfield with given bitflag to initialize bits.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum>::BitField(BitFlag b) : i(b) {}


        /**
        \fn BitField<Enum>::operator BitfieldType() const
        \brief Returns internal value used in bitwise tests.

        Returns internal value used in bitwise test.  Will either be int for
        signed enums, or unsigned int for unsigned enums.

        \return Internal value used in bitwise tests.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum>::operator BitfieldType() const { return i; }


        /**
        \fn BitField<Enum>& BitField<Enum>::operator&=(int)
        \brief Assigns bitfield to result of bitfield & mask

        Performs bitwise AND between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator&=(int mask) { i &= mask; return *this; }

        /**
        \fn BitField<Enum>& BitField<Enum>::operator&=(unsigned int)
        \brief Assigns bitfield to result of bitfield & mask

        Performs bitwise AND between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator&=(unsigned int mask) { i &= mask; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator&=(Enum)
        \brief Assigns bitfield to result of bitfield & enum

        Performs bitwise AND between bitfield and given enum.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator&=(Enum mask) { i &= BitfieldType(mask); return *this; }

        /**
        \fn BitField<Enum>  BitField<Enum>::operator&=(BitField rhs)
        \brief Assigns bitfield to result of bitfield & \a rhs bitfield

        Performs bitwise AND between two bitfields.  Result is
        stored back into first bitfield.
        \return First bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator&=(BitField<Enum> b) { i &= b.i; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator|=(int)
        \brief Assigns bitfield to result of bitfield | mask

        Performs bitwise OR between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator|=(int mask) { i |= mask; return *this; }
        /**
        \fn BitField<Enum>&  BitField<Enum>::operator|=(unsigned int)
        \brief Assigns bitfield to result of bitfield | mask

        Performs bitwise OR between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator|=(unsigned int mask) { i |= mask; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator|=(Enum)
        \brief Assigns bitfield to result of bitfield | Enum

        Performs bitwise OR between bitfield and given enum.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator|=(Enum mask) { i |= BitfieldType(mask); return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator|=(BitField)
        \brief Assigns bitfield to result of bitfield | \a rhs bitfield.

        Performs bitwise OR between two bitfields.  Result is
        stored back into first bitfield.
        \return First bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator|=(BitField<Enum> b) { i |= b.i; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator^=(int)
        \brief Assigns bitfield to result of bitfield ^ mask

        Performs bitwise XOR between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator^=(int mask) { i ^= mask; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator^=(unsigned int)
        \brief Assigns bitfield to result of bitfield ^ mask

        Performs bitwise XOR between bitfield and given value.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator^=(unsigned int mask) { i ^= mask; return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator^=(Enum)
        \brief Assigns bitfield to result of bitfield ^ mask

        Performs bitwise XOR between bitfield and given enum.  Result is
        stored back into bitfield.
        \return Given bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator^=(Enum mask) { i ^= BitfieldType(mask); return *this; }

        /**
        \fn BitField<Enum>&  BitField<Enum>::operator^=(BitField)
        \brief Assigns bitfield to result of bitfield ^ \a rhs bitfield

        Performs bitwise XOR between two bitfields.  Result is
        stored back into first bitfield.
        \return First bitfield with new value stored.
        **/
        template<typename Enum>
        inline BitField<Enum>& BitField<Enum>::operator^=(BitField<Enum> b) { i ^= b.i; return *this; }


        /**
        \fn BitField<Enum> BitField<Enum>::operator&(int) const
        \brief Computes bitwise AND between bitfield and mask

        Computes bitwise AND between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise AND.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator&(int mask) const { return BitField(BitFlag(i & mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator&(unsigned int) const
        \brief Computes bitwise AND between bitfield and mask

        Computes bitwise AND between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise AND.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator&(unsigned int mask) const { return BitField<Enum>(BitFlag(i & mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator&(Enum) const
        \brief Computes bitwise AND between bitfield and enum

        Computes bitwise AND between bitfield and enum.  Returns as new bitfield
        \return Bitfield with results of bitwise AND.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator&(Enum mask) const { return BitField<Enum>(BitFlag(i & BitfieldType(mask))); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator&(BitField<Enum>) const
        \brief Computes bitwise AND between two bitfields

        Computes bitwise AND between two bitfields.  Returns as new bitfield
        \return Bitfield with results of bitwise AND.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator&(BitField<Enum> mask) const { return BitField<Enum>(BitFlag(i & mask.i)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator|(int) const
        \brief Computes bitwise OR between bitfield and mask

        Computes bitwise OR between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise OR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator|(int mask) const { return BitField<Enum>(BitFlag(i | mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator|(unsigned int) const
        \brief Computes bitwise OR between bitfield and mask

        Computes bitwise OR between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise OR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator|(unsigned int mask) const { return BitField<Enum>(BitFlag(i | mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator|(Enum) const
        \brief Computes bitwise OR between bitfield and enum

        Computes bitwise OR between bitfield and enum.  Returns as new bitfield
        \return Bitfield with results of bitwise OR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator|(Enum mask) const { return BitField<Enum>(BitFlag(i | BitfieldType(mask))); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator|(BitField<Enum>) const
        \brief Computes bitwise OR between two bitfields

        Computes bitwise OR between two bitfields.  Returns as new bitfield
        \return Bitfield with results of bitwise OR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator|(BitField<Enum> mask) const { return BitField<Enum>(BitFlag(i | mask.i)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator^(int) const
        \brief Computes bitwise XOR between bitfield and mask

        Computes bitwise XOR between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise XOR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator^(int mask) const { return BitField<Enum>(BitFlag(i ^ mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator^(unsigned int) const
        \brief Computes bitwise XOR between bitfield and mask

        Computes bitwise XOR between bitfield and mask.  Returns as new bitfield
        \return Bitfield with results of bitwise XOR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator^(unsigned int mask) const { return BitField<Enum>(BitFlag(i ^ mask)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator^(Enum) const
        \brief Computes bitwise XOR between bitfield and enum

        Computes bitwise XOR between bitfield and enum.  Returns as new bitfield
        \return Bitfield with results of bitwise XOR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator^(Enum mask) const { return BitField<Enum>(BitFlag(i ^ BitfieldType(mask))); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator^(BitField<Enum>) const
        \brief Computes bitwise XOR between two bitfields

        Computes bitwise XOR between two bitfields.  Returns as new bitfield
        \return Bitfield with results of bitwise XOR.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator^(BitField<Enum> mask) const { return BitField<Enum>(BitFlag(i ^ mask.i)); }

        /**
        \fn BitField<Enum> BitField<Enum>::operator~() const
        \brief Computes bitwise NOT on bitfield

        Computes bitwise NOT on bitfield.  Returns as new bitfield
        \return Bitfield with result of bitwise NOT.
        **/
        template<typename Enum>
        constexpr inline BitField<Enum> BitField<Enum>::operator~() const { return BitField(BitFlag(~i)); }


        /**
        \fn bool BitField<Enum>::operator~() const
        \brief Returns whether any flags are marked (1) in bitfield

        Returns whether any flags are marked (1) in the bitfield.
        **/
        template<typename Enum>
        constexpr inline bool BitField<Enum>::operator!() const { return !i; }


        /**
        \fn bool BitField<Enum>::TestFlag(Enum flag) const
        \brief returns whether enum flag is marked in bitfield

        Performs test to see if flag is marked (1) in bitfield.
        **/
        template<typename Enum>
        constexpr inline bool BitField<Enum>::TestFlag(Enum flag) const { return (i & BitfieldType(flag)) == BitfieldType(flag) && (BitfieldType(flag) != 0 || i == BitfieldType(flag)); }
    }
}
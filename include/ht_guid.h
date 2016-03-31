/**
 **    Hatchit Engine
 **    Copyright(c) 2016 Third-Degree
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
#include <stdint.h>
#include <memory>   // For std::shared_ptr
#include <string>

namespace Hatchit {

    namespace Core {

        /**
         * \class Guid
         * \ingroup HatchitGame
         *
         * \brief Defines a simple globally-unique identifier.
         */
        class HT_API Guid
        {
            uint8_t m_uuid[16];
            uint64_t m_hashCode;
            std::string m_originalString;

        public:
            /**
             * \brief The empty Guid.
             */
            static const Guid Empty;

            /**
             * \brief Creates a new Guid.
             */
            Guid();

            /**
             * \brief Copies one Guid's information into this Guid.
             *
             * \param other The other Guid.
             */
            Guid(const Guid& other);

            /**
             * \brief Moves one Guid's information into this Guid.
             *
             * \param other The other Guid.
             */
            Guid(Guid&& other);

            /**
             * \brief Destroys this Guid.
             */
            ~Guid();

            /**
             * \brief Gets this Guid's hash code.
             *
             * Provides a 64-bit unsigned integer hash representation of this Guid.
             */
            uint64_t GetHashCode() const;

            /**
             * \brief Gets this Guid's original string, if there is one.
             *
             * \return The original string, if it exists.
             */
            std::string GetOriginalString() const;

            /**
             * \brief Checks to see if this Guid is originally from a string.
             *
             * \return True if this Guid is based off of a string, false if not.
             */
            bool IsFromString() const;

            /**
             * \brief Gets the textual representation of this Guid.
             *
             * Returns the textual representation of this Guid, in the form
             * of {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}.
             */
            std::string ToString() const;

            /**
             * \brief Checks to see if this Guid is the same as another.
             *
             * \param other The other Guid.
             */
            bool operator==(const Guid& other) const;

            /**
             * \brief Checks to see if this Guid is not the same as another.
             *
             * \param other The other Guid.
             */
            bool operator!=(const Guid& other) const;

            /**
             * \brief Copies one Guid's information into this Guid.
             *
             * \param other The other Guid.
             */
            Guid& operator=(const Guid& other);

            /**
             * \brief Moves one Guid's information into this Guid.
             *
             * \param other The other Guid.
             */
            Guid& operator=(Guid&& other);

        public:
            /**
             * \brief Creates a Guid from a string by hashing the string.
             *
             * \param text The text to create a Guid from.
             * \return The Guid based off of the given text.
             */
            static Guid FromString(const std::string& text);

            /**
            * \brief Attempts to parse a Guid from its textual representation.
            *
            * \param text The text to parse.
            * \param out The Guid to fill with information.
            * \return True if parsing was successful, false if not.
            */
            static bool Parse(const std::string& text, Guid& out);
        };

    }
}

namespace std {

    /**
     * \class hash<Hatchit::Game::Guid>
     * \ingroup std
     *
     * \brief Defines a hash struct to allow Hatchit::Game::Guid's to be used as keys in STL structures.
     */
    template<> struct hash<Hatchit::Core::Guid>
    {
        inline size_t operator()(const Hatchit::Core::Guid& guid) const
        {
            return guid.GetHashCode();
        }
    };

}

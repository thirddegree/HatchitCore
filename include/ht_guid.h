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

        public:
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
             * \brief Hashes this Guid.
             *
             * Provides a 64-bit unsigned integer hash representation of this Guid.
             */
            uint64_t Hash() const;

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
            return guid.Hash();
        }
    };

}

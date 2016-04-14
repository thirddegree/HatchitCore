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

//Header includes
#include <ht_platform.h> //HT_API
#include <stdint.h> //uint8_t & uint64_t typedef
#include <string> //std::string typedef

namespace Hatchit
{
    namespace Core
    {

        /**
         * \class Guid
         * \ingroup HatchitCore
         *
         * \brief Defines a simple globally-unique identifier.
         */
        class HT_API Guid
        {
        public:
            //Static Methods
            static Guid FromString(const std::string& text);

            static bool Parse(const std::string& text, Guid& out);

            //Static Variables
            static const Guid Empty;


            Guid();

            Guid(const Guid& other);

            Guid(Guid&& other);

            ~Guid();

            //Public Methods

            uint64_t GetHashCode() const;

            std::string GetOriginalString() const;

            bool IsFromString() const;

            std::string ToString() const;

            bool operator==(const Guid& other) const;

            bool operator!=(const Guid& other) const;

            Guid& operator=(const Guid& other);

            Guid& operator=(Guid&& other);


        private:
            //Private Variables
            uint8_t m_uuid[16];
            uint64_t m_hashCode;
            std::string m_originalString;
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
        size_t operator()(const Hatchit::Core::Guid& guid) const;
    };
}

#include <ht_guid.inl>
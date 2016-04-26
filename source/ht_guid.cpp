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

#include <ht_guid.h>
#include <chrono>
#include <random>
#include <sstream>
#include <string.h>
#include <time.h>

namespace Hatchit {

    namespace Core {

        namespace
        {
            /**
             * \brief Defines a simple Guid helper.
             */
            struct GuidHelper
            {
                static GuidHelper s_Instance;

                std::mt19937_64 m_mersenneTwister;
                std::uniform_int_distribution<uint32_t> m_distribution;

                /**
                 * \brief Creates a new Guid helper.
                 */
                GuidHelper()
                    : m_distribution(0, 255)
                {
                    using Clock = std::chrono::high_resolution_clock;
                    using TimePoint = Clock::time_point;

                    // We need to seed the PRNG, so let's use a high-resolution time since the epoch
                    TimePoint epoch;
                    TimePoint now = Clock::now();
                    auto duration = now - epoch;
                    m_mersenneTwister.seed(static_cast<uint64_t>(duration.count()));
                }

                /**
                 * \brief Generates a high-quality random byte.
                 */
                static inline uint8_t GenerateByte()
                {
                    return static_cast<uint8_t>(s_Instance.m_distribution(s_Instance.m_mersenneTwister));
                }
            };

            GuidHelper GuidHelper::s_Instance;
        }

        /**
         * \brief Performs an FNV-1a hash on the given buffer.
         *
         * \param buffer The buffer to hash.
         * \param bufferLen The buffer's length.
         * \return The hash.
         */
        static uint64_t GetFnv1aHash(const void* buffer, uint64_t bufferLen)
        {
            // This is adapted from the 64-bit version of the FNV-1a hashing algorithm
            // Source:  http://www.isthe.com/chongo/tech/comp/fnv/
            // License: Public Domain

            uint64_t hash = 0;
            const uint8_t* byteBuffer = static_cast<const uint8_t*>(buffer);

            for (uint64_t index = 0; index < bufferLen; ++index)
            {
                hash ^= static_cast<uint64_t>(byteBuffer[index]);

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

        /**
         * \brief Creates an empty Guid.
         *
         * \return An empty Guid.
         */
        static Guid CreateEmptyGuid()
        {
            Guid a, b;
            b = std::move(a);
            return a;
        }

        /**
        * \brief Maps a hexadecimal character to its decimal equivalent.
        *
        * \param hex The hexadecimal character.
        * \param out The value to output to.
        * \return True if the mapping was successful, false if not.
        */
        static inline bool MapHexToDec(char hex, uint8_t& out)
        {
            if (hex >= '0' && hex <= '9') { out = hex - '0';      return true; }
            if (hex >= 'a' && hex <= 'f') { out = hex - 'a' + 10; return true; }
            if (hex >= 'A' && hex <= 'F') { out = hex - 'A' + 10; return true; }
            return false;
        }

        /**
        * \brief Parses a byte from text.
        *
        * \param text The text to parse from.
        * \param position The position in the text to parse from.
        * \param out The output byte.
        * \return True if parsing was successful, false if not.
        */
        static inline bool ParseByte(const std::string& text, size_t position, uint8_t& out)
        {
            if (position + 1 < text.length())
            {
                // Map the first and second character to their respective characters
                uint8_t first = 0, second = 0;
                if (MapHexToDec(text[position], first) && MapHexToDec(text[position + 1], second))
                {
                    out = first * 16 + second;
                    return true;
                }
            }
            return false;
        }

        //ALL Static Methods
        /**
        * \brief Creates a Guid from a string by hashing the string.
        *
        * \param text The text to create a Guid from.
        * \return The Guid based off of the given text.
        */
        Guid Guid::FromString(const std::string& text)
        {
            // If the text is empty, then return an empty Guid
            if (text.empty())
            {
                return Guid::Empty;
            }

            // To do this, we'll hash the first half and the second half of the string
            // and then copy the bytes over (will be 16 total bytes)
            size_t half = text.length() / 2;
            uint64_t firstHash = GetFnv1aHash(text.c_str(), half);
            uint64_t secondHash = GetFnv1aHash(text.c_str() + half, text.length() - half);

            Guid guid;
            memcpy(guid.m_uuid, &firstHash, 8);
            memcpy(guid.m_uuid + 8, &secondHash, 8);
            guid.m_hashCode = GetFnv1aHash(guid.m_uuid, 16);
            guid.m_originalString = text;

            return guid;
        }

        /**
        * \brief Attempts to parse a Guid from its textual representation.
        *
        * \param text The text to parse.
        * \param out The Guid to fill with information.
        * \return True if parsing was successful, false if not.
        */
        bool Guid::Parse(const std::string& text, Guid& out)
        {
            if (text.length() != 38)
            {
                return false;
            }

            if (text[0] != '{' && text[37] != '}')
            {
                return false;
            }

            // 01234567890123456789012345678901234567
            // {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}
            size_t offs = 1;
            for (size_t index = 0; index < 16; ++index)
            {
                size_t position = offs + index * 2;
                switch (text[position])
                {
                case '-':
                    ++offs;
                    --index;
                    break;
                default:
                    uint8_t byte = 0;
                    if (!ParseByte(text, position, byte))
                    {
                        return false;
                    }
                    out.m_uuid[index] = byte;
                    break;
                }
            }

            out.m_hashCode = GetFnv1aHash(out.m_uuid, 16);

            return true;
        }

        // Declare the empty Guid

        /**
        * \brief The empty Guid.
        */
        const Guid Guid::Empty = CreateEmptyGuid();

        /**
        \fn const Guid& Guid::GetEmpty()
        \brief Returns reference to empty guid.
        **/
        const Guid& Guid::GetEmpty()
        {
            return Empty;
        }

        /**
         * \brief Creates a new Guid.
         */
        Guid::Guid()
            : m_hashCode(0)
        {
            // Generate the GUID bytes
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = GuidHelper::GenerateByte();
            }

            // Get the hash code
            m_hashCode = GetFnv1aHash(m_uuid, 16);
        }

        /**
         * \brief Copies one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid::Guid(const Guid& other)
        {
            *this = other;
        }

        /**
         * \brief Moves one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid::Guid(Guid&& other)
        {
            *this = other;
        }

        /**
         * \brief Destroys this Guid.
         */
        Guid::~Guid()
        {
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = 0;
            }
        }

       //Public Methods

        /**
         * \brief Hashes this Guid.
         *
         * Provides a 64-bit unsigned integer hash representation of this Guid.
         */
        uint64_t Guid::GetHashCode() const
        {
            return m_hashCode;
        }
        
        /**
         * \brief Gets this Guid's original string, if there is one.
         *
         * \return The original string, if it exists.
         */
        std::string Guid::GetOriginalString() const
        {
            return m_originalString;
        }

        /**
         * \brief Checks to see if this Guid is originally from a string.
         *
         * \return True if this Guid is based off of a string, false if not.
         */
        bool Guid::IsFromString() const
        {
            return !m_originalString.empty();
        }

        /**
         * \brief Gets the textual representation of this Guid.
         *
         * Returns the textual representation of this Guid, in the form
         * of {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}.
         */
        std::string Guid::ToString() const
        {
            std::ostringstream stream;
            stream << '{' << std::hex;

            for (int index = 0; index < 16; ++index)
            {
                // TODO - Get std::setfill and std::setw to work ... eventually
                if (m_uuid[index] < 16)
                {
                    stream << '0';
                }

                stream << static_cast<int>(m_uuid[index]);

                switch (index)
                {
                    case 3:
                    case 5:
                    case 7:
                    case 9:
                        stream << '-';
                        break;
                }
            }

            stream << '}';
            return stream.str();
        }

        /**
         * \brief Checks to see if this Guid is the same as another.
         *
         * \param other The other Guid.
         */
        bool Guid::operator==(const Guid& other) const
        {
            return m_hashCode == other.m_hashCode;
        }

        /**
         * \brief Checks to see if this Guid is not the same as another.
         *
         * \param other The other Guid.
         */
        bool Guid::operator!=(const Guid& other) const
        {
            return m_hashCode != other.m_hashCode;
        }

        /**
        \fn bool Guid::operator<(const Guid& other) const
        \brief Comparison function used for sorting

        Provides a consistent comparison function for sorting
        **/
        bool Guid::operator<(const Guid& other) const
        {
            return m_hashCode < other.m_hashCode;
        }

        /**
        \fn bool Guid::operator>(const Guid& other) const
        \brief Comparison function used for sorting

        Provides a consistent comparison function for sorting.
        **/
        bool Guid::operator>(const Guid& other) const
        {
            return m_hashCode > other.m_hashCode;
        }

        /**
         * \brief Copies one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid& Guid::operator=(const Guid& other)
        {
            // Copy GUID bytes
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = other.m_uuid[index];
            }

            // Copy hash code
            m_hashCode = other.m_hashCode;

            // Copy original string
            m_originalString = other.m_originalString;

            return *this;
        }

        /**
         * \brief Moves one Guid's information into this Guid.
         *
         * \param other The other Guid.
         */
        Guid& Guid::operator=(Guid&& other)
        {
            // Move GUID bytes
            for (int index = 0; index < 16; ++index)
            {
                m_uuid[index] = other.m_uuid[index];
                other.m_uuid[index] = 0;
            }

            // Move hash code
            m_hashCode = other.m_hashCode;
            other.m_hashCode = 0;

            // Move original string
            m_originalString = other.m_originalString;
            other.m_originalString = "";

            return *this;
        }

    }
}

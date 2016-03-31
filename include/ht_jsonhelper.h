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

#include <json.hpp>
#include <ht_guid.h>
#if defined(_DEBUG) || defined(DEBUG)
#  include <ht_debug.h>
#endif

namespace Hatchit {

    namespace Core {

        /**
         * \brief The JSON type to use.
         */
        using JSON = nlohmann::json;

#if defined(_DEBUG) || defined(DEBUG)

        /**
         * \brief The verification function used to validate JSON types.
         */
        using JsonVerifyFunc = bool(JSON::*)() const;

        /**
         * \brief Attempts to extract a value from a JSON object.
         *
         * \param json The JSON object.
         * \param verify The JSON type verification function.
         * \param name The name of the value to retrieve.
         * \param out The output variable.
         * \return True if the extraction was successful, false if not.
         */
        template<typename T>
        static inline bool _JsonExtractValue(const JSON& json, JsonVerifyFunc verify, const std::string& name, T& out)
        {
            auto  search = json.find(name);
            auto& object = *search;

            if (search == json.end() || !(object.*verify)())
            {
                HT_DEBUG_PRINTF("[JSON] Failed to extract '%s' from object as desired type.\n", name);
                return false;
            }

            out = search->get<T>();
            return true;
        }

        /**
         * \brief Attempts to extract a string from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the string to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractString(json, name, out) _JsonExtractValue<std::string>(json, &JSON::is_string, name, out)

		 /**
		 * \brief Attempts to extract a float from a JSON object.
		 *
		 * \param json The JSON object.
		 * \param name The name of the float to retrieve.
		 * \param out The output float.
		 * \return True if the extraction was successful, false if not.
		 */
		#define JsonExtractFloat(json, name, out) _JsonExtractValue<float>(json, &JSON::is_number_float, name, out)

        /**
         * \brief Attempts to extract a double from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the double to retrieve.
         * \param out The output double.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractDouble(json, name, out) _JsonExtractValue<double>(json, &JSON::is_number_float, name, out)

        /**
         * \brief Attempts to extract a float from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the float to retrieve.
         * \param out The output bool.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractBool(json, name, out) _JsonExtractValue<bool>(json, &JSON::is_boolean, name, out)

		 /**
		 * \brief Attempts to extract a int32 from a JSON object.
		 *
		 * \param json The JSON object.
		 * \param name The name of the int32 to retrieve.
		 * \param out The output int32.
		 * \return True if the extraction was successful, false if not.
		 */
		#define JsonExtractInt32(json, name, out) _JsonExtractValue<int32_t>(json, &JSON::is_number_integer, name, out)

		 /**
		 * \brief Attempts to extract a uint32 from a JSON object.
		 *
		 * \param json The JSON object.
		 * \param name The name of the uint32 to retrieve.
		 * \param out The output uint32.
		 * \return True if the extraction was successful, false if not.
		 */
		#define JsonExtractUInt32(json, name, out) _JsonExtractValue<uint32_t>(json, &JSON::is_number_integer, name, out)

        /**
         * \brief Attempts to extract an int64 from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the int64 to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractInt64(json, name, out) _JsonExtractValue<int64_t>(json, &JSON::is_number_integer, name, out)

        /**
         * \brief Attempts to extract a uint64 from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the uint64 to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractUint64(json, name, out) _JsonExtractValue<uint64_t>(json, &JSON::is_number_unsigned, name, out)

        /**
         * \brief Attempts to extract a Guid from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the Guid to retrieve.
         * \param out The output Guid.
         * \return True if the extraction was successful, false if not.
         */
        static __forceinline bool JsonExtractGuid(const JSON& json, const std::string& name, Guid& out)
        {
			std::string guidText;
            return JsonExtractString(json, name, guidText) && Guid::Parse(guidText, out);
        }

		/**
         * \brief Attempts to extract a Guid from a JSON object.
         *
         * \param name The string representing the Guid.
         * \param out The output Guid.
         * \return True if the extraction was successful, false if not.
         */
        static __forceinline bool JsonExtractGuid(const std::string& name, Guid& out)
        {
            return Guid::Parse(name, out);
        }

#else

        /**
         * \brief Attempts to extract a string from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the string to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractString(json, name, out) out = json[name].get<std::string>()
        
        /**
         * \brief Attempts to extract a double from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the double to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractDouble(json, name, out) out = json[name]
        
        /**
         * \brief Attempts to extract a float from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the float to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractBool(json, name, out) out = json[name]
        
        /**
         * \brief Attempts to extract an int64 from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the int64 to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractInt64(json, name, out) out = json[name]
        
        /**
         * \brief Attempts to extract a uint64 from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the uint64 to retrieve.
         * \param out The output string.
         * \return True if the extraction was successful, false if not.
         */
        #define JsonExtractUint64(json, name, out) out = json[name]

        /**
         * \brief Attempts to extract a Guid from a JSON object.
         *
         * \param json The JSON object.
         * \param name The name of the Guid to retrieve.
         * \param out The output Guid.
         * \return True if the extraction was successful, false if not.
         */
        static __forceinline bool JsonExtractGuid(const JSON& json, const std::string& name, Guid& out)
        {
            std::string guidText;
            JsonExtractString(json, name, guidText);
            return Guid::Parse(guidText, out);
        }

#endif

    }

}

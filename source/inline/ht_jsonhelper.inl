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

#include <ht_jsonhelper.h>

namespace Hatchit
{
    namespace Core
    {
        namespace
        {
            /**
            * \fn bool _JsonExtractValue(
                const JSON& json,
                JsonVerifyFunc verify,
                const std::string& name,
                T& out)
            * \brief Attempts to extract a value from a JSON object.
            *
            * \param json The JSON object.
            * \param verify The JSON type verification function.
            * \param name The name of the value to retrieve.
            * \param out The output variable.
            * \return True if the extraction was successful, false if not.
            * 
            * \note Please prefer to call JsonExtract<T> if you are using this
            * function to simply get data from JSON.  If you are writing your own
            * overload to JsonExtract<T>, feel free to use this function.
            */
            template<typename T>
            inline bool _JsonExtractValue(
                const JSON& json,
                JsonVerifyFunc verify,
                const std::string& name,
                T& out)
            {
#if defined(_DEBUG) || defined(DEBUG)
                auto  search = json.find(name);
                if (search == json.end())
                {
                    HT_DEBUG_PRINTF("[JSON] Failed to extract '%s' from object.\n", name);
                    return false;
                }

                const JSON& obj = *search;
                if (!(obj.*verify)())
                {
                    HT_DEBUG_PRINTF("[JSON] Failed to verify type of '%s' extracted from object.\n", name);
                    return false;
                }

                out = obj.get<T>();
                return true;
#else
#   if defined(HT_DISABLE_JSON_CHECKS)
                out = json[name].get<T>();
                return true;
#   else
                auto  search = json.find(name);
                auto& object = *search;

                out = object.get<T>();
                return (object.*verify)();
#   endif
#endif
            }
        }

        template<typename T>
        inline bool JsonExtract(
            const JSON& json,
            const std::string& name,
            T& out)
        {
            //Removed for GCC compilation. 
            //TODO: Find cross platform solution.
            //static_assert(false, "Extraction is not defined for this type!");
            return false;
        }

        /**
        * \brief Attempts to extract a json object from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the object to retrieve.
        * \param out The output object.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<JSON::object_t>(
            const JSON& json,
            const std::string& name,
            JSON::object_t& out)
        {
            return _JsonExtractValue<JSON::object_t>(
                json,
                &JSON::is_object,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a std::vector from a JSON object.
        * \tparam T A JSON value type.
        * \param json   The JSON object to examine.
        * \param key    The key to locate in the JSON object.
        * \param value  The std::vector to insert into.
        * \return true if the std::vector could be successfully extracted.
        */
        template <typename Container>
        inline bool JsonExtractContainer(const JSON& json, const std::string& key, Container& value)
        {
            JSON::const_iterator iter = json.find(key);
            if (iter == json.cend() || !iter->is_array())
            {
                return false;
            }

            value = iter->get<Container>();

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
        template<>
        inline bool JsonExtract<std::string>(
            const JSON& json,
            const std::string& name,
            std::string& out)
        {
            return _JsonExtractValue<std::string>(
                json,
                &JSON::is_string,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a double from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the double to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<double>(
            const JSON& json,
            const std::string& name,
            double& out)
        {
            return _JsonExtractValue<double>(
                json,
                &JSON::is_number_float,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a float from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the float to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<float>(
            const JSON& json,
            const std::string& name,
            float& out)
        {
            return _JsonExtractValue<float>(
                json,
                &JSON::is_number_float,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a float from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the float to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<bool>(
            const JSON& json,
            const std::string& name,
            bool& out)
        {
            return _JsonExtractValue<bool>(
                json,
                &JSON::is_boolean,
                name,
                out);
        }

        /**
        * \brief Attempts to extract an int64 from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the int64 to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<int64_t>(
            const JSON& json,
            const std::string& name,
            int64_t& out)
        {
            return _JsonExtractValue<int64_t>(
                json,
                &JSON::is_number_integer,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a uint64 from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the uint64 to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<uint64_t>(
            const JSON& json,
            const std::string& name,
            uint64_t& out)
        {
            return _JsonExtractValue<uint64_t>(
                json,
                &JSON::is_number_unsigned,
                name,
                out);
        }

        /**
        * \brief Attempts to extract an int32 from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the int32 to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<int32_t>(
            const JSON& json,
            const std::string& name,
            int32_t& out)
        {
            return _JsonExtractValue<int32_t>(
                json,
                &JSON::is_number_integer,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a uint32 from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the uint32 to retrieve.
        * \param out The output string.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<uint32_t>(
            const JSON& json,
            const std::string& name,
            uint32_t& out)
        {
            return _JsonExtractValue<uint32_t>(
                json,
                &JSON::is_number_unsigned,
                name,
                out);
        }

        /**
        * \brief Attempts to extract a Guid from a JSON object.
        *
        * \param json The JSON object.
        * \param name The name of the Guid to retrieve.
        * \param out The output Guid.
        * \return True if the extraction was successful, false if not.
        */
        template<>
        inline bool JsonExtract<Guid>(
            const JSON& json,
            const std::string& name,
            Guid& out)
        {
            std::string guidText;
            return JsonExtract<std::string>(json, name, guidText)
                && Guid::Parse(guidText, out);
        }
    }
}

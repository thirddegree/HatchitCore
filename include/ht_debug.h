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

#include <string>
#include <fstream>
#include <ht_platform.h>
#include <format.h>


#ifndef HT_STRINGIFY
#  define HT_STRINGIFY(x) #x
#endif

#ifndef HT_SFY_
#  define HT_SFY_(x) HT_STRINGIFY(x)
#endif

#ifndef HT_INFO_PRINTF
#  define HT_INFO_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Info, message, __VA_ARGS__)
#endif

#ifndef HT_DEBUG_PRINTF
#  define HT_DEBUG_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Debug, message, __VA_ARGS__)
#endif

#ifndef HT_WARNING_PRINTF
#  define HT_WARNING_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Warning, message, __VA_ARGS__)
#endif

#ifndef HT_ERROR_PRINTF
#  define HT_ERROR_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Error, message, __VA_ARGS__)
#endif

namespace Hatchit {

    namespace Core {

        /**
         * \brief Defines a static debug class.
         */
        class HT_API Debug
        {
        public:
            /**
             * \brief An enumeration of log severities.
             */
            enum class LogSeverity
            {
                Debug,
                Info,
                Warning,
                Error
            };

            /**
             * \brief Gets the current severity threshold.
             *
             * If a message is logged with a severity lower than the current severity
             * threshold, then it will not be output for end-users to see.
             */
            static Debug::LogSeverity GetSeverityThreshold();
            
            /**
             * \brief Logs a message with the given severity.
             *
             * \brief severity The message's severity.
             * \brief fmt_message The message that is to be formatted.
             * \brief args The arguments to format the message with.
             */
            template<class ... Args>
            static void Log(Debug::LogSeverity severity, const std::string& fmt_message, const Args& ... args);

            /**
             * \brief Sets the current severity threshold.
             *
             * \param threshold The new severity threshold.
             */
            static void SetSeverityThreshold(LogSeverity threshold);

        private:
            /**
             * \brief Logs the given message.
             *
             * \param message The message to log.
             */
            static void LogMessage(const std::string& message);

            /**
             * \brief Checks the given severity level and determines whether
             *        or not a message should be logged.
             *
             * \param severity The severity level of the message to log.
             */
            static bool ShouldLogSeverity(Debug::LogSeverity severity);

            static Debug::LogSeverity m_severityThreshold;
        };

    }
}

#include <ht_debug.inl>

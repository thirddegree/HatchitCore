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
 * \file ht_debug.h
 * \brief Defines various debug utilities
 * \author Matt Guerrette (direct3Dtutorials@gmail.com)
 * \author Third-Degree contributors (https://github.com/thirddegree)
 *
 * This file contains various debug utility functions
 * and macros
 */

#include <string>           // For std::string
#include <fstream>          // For std::ofstream
#include <memory>           // For std::unique_ptr
#include <functional>       // For std::function
#include <ht_platform.h>    // For HT_API
#include <format.h>         // For fmt::sprintf

/**
 * \def HT_STRINGIFY(x)
 * Defines macro to return string form of input
 */
#if !defined(HT_STRINGIFY)
    #define HT_STRINGIFY(x) #x
#endif

/**
 * \def HT_SFY_(x)
 * Defines macro wrapper for HT_STRINGIFY
 */
#if !defined(HT_SFY_)
    #define HT_SFY_(x) HT_STRINGIFY(x)
#endif

/**
 * \def HT_FUNCTION
 * Defines platform specific function signature macro
 *
 */
#ifndef HT_FUNCTION
    #ifdef HT_SYS_LINUX
        #define HT_FUNCTION __PRETTY_FUNCTION__
    #else
        #define HT_FUNCTION __FUNCSIG__
    #endif
#endif

/**
 * \def HT_DEBUG_PRINTF(x)
 * Defines debug print macro that can be used to log debug text at runtime.
 * NOTE: This macro is only active for Debug builds.
 */
#if !defined(HT_DEBUG_PRINTF) && (defined(_DEBUG) || defined(DEBUG))
    #define HT_DEBUG_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Debug, message, ##__VA_ARGS__)
#else
    #define HT_DEBUG_PRINTF(message, ...)
#endif

#if !defined(HT_INFO_PRINTF)
    #define HT_INFO_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Info, message, ##__VA_ARGS__)
#endif

#if !defined(HT_WARNING_PRINTF)
    #define HT_WARNING_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Warning, message, ##__VA_ARGS__)
#endif

#if !defined(HT_ERROR_PRINTF)
    #define HT_ERROR_PRINTF(message, ...) Hatchit::Core::Debug::Log(Hatchit::Core::Debug::LogSeverity::Error, message, ##__VA_ARGS__)
#endif

/**
 * \namespace Hatchit
 * \brief Engine global layer
 * \defgroup Hatchit
 */
namespace Hatchit {

    /**
     * \namespace Hatchit::Core
     * \brief Engine utility layer
     * \defgroup Core
     */
    namespace Core {

        /**
         * \ingroup Core
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
             * \brief The type used for registering log callbacks.
             */
            using LogCallback = std::function<void(const std::string&)>;

            /**
             * \brief Gets the file name of the output file.
             *
             * \return The output file name.
             */
            static std::string GetOutputFileName();

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
             * \brief Sets the callback for whenever a message is logged.
             *
             * \param callback The new callback.
             */
            static void SetLogCallback(LogCallback callback);

            /**
             * \brief Sets the file name of the output file.
             * \warning This function will not do anything after the first time something is logged.
             *
             * \param fname The new file name.
             */
            static void SetOutputFileName(const std::string& fname);

            /**
             * \brief Sets the current severity threshold.
             *
             * \param threshold The new severity threshold.
             */
            static void SetSeverityThreshold(LogSeverity threshold);

        private:
            /**
             * \brief Creates a full log message, including severity and a timestamp.
             *
             * \param severity The message severity.
             * \param message The formatted user message.
             * \return The full log message.
             */
            static std::string CreateLogMessage(Debug::LogSeverity severity, std::string message);

            /**
             * \brief Generates a timestamp.
             *
             * \return The timestamp.
             */
            static std::string GenerateTimestamp();

            /**
             * \brief Initializes the output stream.
             */
            static void InitializeOutputStream();

            /**
             * \brief Logs the given message.
             *
             * \param message The formatted message.
             * \param tryOpenFile True to try to open the output file, false to not.
             */
            static void LogMessage(const std::string& message, bool tryOpenFile);

            /**
             * \brief Checks the given severity level and determines whether
             *        or not a message should be logged.
             *
             * \param severity The severity level of the message to log.
             */
            static bool ShouldLogSeverity(Debug::LogSeverity severity);

            static const std::string s_severityStrings[4];
            static LogCallback s_logCallback;
            static std::string s_outputFile;
            static std::unique_ptr<std::ofstream> s_outputStream;
            static Debug::LogSeverity s_severityThreshold;
            static bool s_canLogToFile;
        };

    }
}

#include <ht_debug.inl>

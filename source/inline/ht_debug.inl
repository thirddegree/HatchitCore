#pragma once

#include <ht_debug.h>

namespace Hatchit {

    namespace Core {

        /**
         * \brief Logs a message with the given severity.
         *
         * \brief severity The message's severity.
         * \brief fmt_message The message that is to be formatted.
         * \brief args The arguments to format the message with.
         */
        template<class ... Args>
        void Debug::Log(Debug::LogSeverity severity, const std::string& fmt_message, const Args& ... args)
        {
            static const std::string s_messagePrefixes[4] =
            {
                std::string("[DEBUG] "),
                std::string("[INFO]  "),
                std::string("[WARN]  "),
                std::string("[ERROR] "),
            };

            if (ShouldLogSeverity(severity))
            {
                std::string message = fmt::sprintf(fmt_message, args ...);
                std::string prefix = s_messagePrefixes[static_cast<int>(severity)];
                LogMessage(prefix + message);
            }
        }

    }
}
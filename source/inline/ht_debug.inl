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
            if (!ShouldLogSeverity(severity))
            {
                return;
            }

            std::string message = fmt::sprintf(fmt_message, args ...);
            message = Debug::CreateLogMessage(severity, message);

            LogMessage(message, true);
        }

    }
}
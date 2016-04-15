#include <ht_debug.h>
#include <iostream>
#if defined(HT_SYS_WINDOWS)
#  include <debugapi.h>
#endif

namespace Hatchit {

    namespace Core {

#if defined(_DEBUG) || defined(DEBUG)
        Debug::LogSeverity Debug::m_severityThreshold = Debug::LogSeverity::Debug;
#else
        Debug::LogSeverity Debug::m_severityThreshold = Debug::LogSeverity::Info;
#endif

        /**
         * \brief Gets the current severity threshold.
         *
         * If a message is logged with a severity lower than the current severity
         * threshold, then it will not be output for end-users to see.
         */
        Debug::LogSeverity Debug::GetSeverityThreshold()
        {
            return m_severityThreshold;
        }

        /**
         * \brief Logs the given message.
         *
         * \param message The message to log.
         */
        void Debug::LogMessage(const std::string& message)
        {
#if defined(HT_SYS_WINDOWS)
            OutputDebugStringA(message.c_str());
#endif

            std::cerr << message.c_str();
        }

        /**
         * \brief Sets the current severity threshold.
         *
         * \param threshold The new severity threshold.
         */
        void Debug::SetSeverityThreshold(Debug::LogSeverity threshold)
        {
            m_severityThreshold = threshold;
        }

        /**
         * \brief Checks the given severity level and determines whether
         *        or not a message should be logged.
         *
         * \param severity The severity level of the message to log.
         */
        bool Debug::ShouldLogSeverity(Debug::LogSeverity severity)
        {
            return static_cast<int>(severity) >= static_cast<int>(m_severityThreshold);
        }

    }

}

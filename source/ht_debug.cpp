#include <ht_debug.h>       // For Debug::*
#include <ht_os.h>
#include <iostream>         // For std::cout
#include <ctime>            // For std::time, std::localtime
#if defined(HT_SYS_WINDOWS)
    #include <debugapi.h>   // For OutputDebugMessageA
#endif
#include <memory>

namespace Hatchit {

    namespace Core {

        Debug::LogCallback              Debug::s_logCallback;
        std::unique_ptr<std::ofstream>  Debug::s_outputStream;
        bool                            Debug::s_canLogToFile = false;
        const std::string               Debug::s_severityStrings[4] =
        {
            std::string("[DEBUG]"),
            std::string("[INFO] "),
            std::string("[WARN] "),
            std::string("[ERROR]"),
        };
#if defined(_DEBUG) || defined(DEBUG)
        Debug::LogSeverity              Debug::s_severityThreshold = Debug::LogSeverity::Debug;
#else
        Debug::LogSeverity              Debug::s_severityThreshold = Debug::LogSeverity::Info;
#endif

        /**
         * \brief Creates a full log message, including severity and a timestamp.
         *
         * \param severity The message severity.
         * \param message The formatted user message.
         * \return The full log message.
         */
        std::string Debug::CreateLogMessage(Debug::LogSeverity severity, std::string message)
        {
            return fmt::sprintf("%s %s %s", GenerateTimestamp(), s_severityStrings[static_cast<int>(severity)], message);
        }

        /**
         * \brief Generates a timestamp.
         *
         * \return The timestamp.
         */
        std::string Debug::GenerateTimestamp()
        {
            std::time_t time_epoch = std::time(nullptr);
            tm*         time_local = std::localtime(&time_epoch);

            return fmt::sprintf("[%02d:%02d:%02d]", time_local->tm_hour, time_local->tm_min, time_local->tm_sec);
        }

        /**
         * \brief Gets the file name of the output file.
         *
         * \return The output file name.
         */
        std::string Debug::GetOutputFileName()
        {
            return os_exec_dir() + os_exec_name() + ".log";
        }

        /**
         * \brief Gets the current severity threshold.
         *
         * If a message is logged with a severity lower than the current severity
         * threshold, then it will not be output for end-users to see.
         */
        Debug::LogSeverity Debug::GetSeverityThreshold()
        {
            return s_severityThreshold;
        }

        /**
         * \brief Initializes the output stream.
         */
        void Debug::InitializeOutputStream()
        {
            bool canLog = true;

            // Create the stream
            if (!s_outputStream)
            {
                s_outputStream = std::make_unique<std::ofstream>();
                if (!s_outputStream)
                {
                    LogMessage(CreateLogMessage(LogSeverity::Error, "Failed to allocate output file stream.\n"), false);
                    canLog = false;
                }
            }

            // Open the file
            if (s_outputStream)
            {
                s_outputStream->open(GetOutputFileName(), std::ios::app | std::ios::binary);
                if (!s_outputStream->is_open())
                {
                    // We need to use LogMessage instead of Log here so that we don't try to open the file again
                    LogMessage(CreateLogMessage(LogSeverity::Error, "Failed to open output file '" + GetOutputFileName() + "'.\n"), false);
                    canLog = false;
                }
            }

            s_canLogToFile = canLog;

            // If we can log to the file, add some kind of separator
            if (canLog)
            {
                std::time_t time_epoch = std::time(nullptr);
                tm*         time_local = std::localtime(&time_epoch);
                std::string separator = fmt::sprintf(
                    "------- LOG FILE OPENED ON %02d/%02d/%d -------\n",
                    time_local->tm_mon + 1,
                    time_local->tm_mday,
                    time_local->tm_year + 1900);
                LogMessage(CreateLogMessage(LogSeverity::Info, separator), false);
            }
        }

        /**
         * \brief Logs the given message.
         *
         * \param message The formatted message.
         * \param tryOpenFile True to try to open the output file, false to not.
         */
        void Debug::LogMessage(const std::string& message, bool tryOpenFile)
        {
            // If we should try to open the file then, well, try to open it
            if (tryOpenFile && !s_canLogToFile)
            {
                InitializeOutputStream();
            }

#if defined(HT_SYS_WINDOWS)
            // Output to the Visual Studio debug window
            OutputDebugStringA(message.c_str());
#endif

            // Output to the console and file
            std::cout << message.c_str();
            if (s_canLogToFile)
            {
                (*s_outputStream) << message.c_str();
            }

            // Invoke the callback
            if (s_logCallback)
            {
                s_logCallback(message);
            }
        }

        /**
         * \brief Sets the callback for whenever a message is logged.
         *
         * \param callback The new callback.
         */
        void Debug::SetLogCallback(LogCallback callback)
        {
            s_logCallback = callback;
        }

        /**
         * \brief Sets the current severity threshold.
         *
         * \param threshold The new severity threshold.
         */
        void Debug::SetSeverityThreshold(Debug::LogSeverity threshold)
        {
            s_severityThreshold = threshold;
        }

        /**
         * \brief Checks the given severity level and determines whether
         *        or not a message should be logged.
         *
         * \param severity The severity level of the message to log.
         */
        bool Debug::ShouldLogSeverity(Debug::LogSeverity severity)
        {
            return static_cast<int>(severity) >= static_cast<int>(s_severityThreshold);
        }

    }

}

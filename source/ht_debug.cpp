#include <ht_debug.h>       // For Debug::*
#include <ht_os.h>
#include <iostream>         // For std::cout
#include <ctime>            // For std::time, std::localtime

#if defined(HT_SYS_WINDOWS)
    #include <debugapi.h>
#ifdef HT_WINDOWS_STORE_APP
    #include <ht_winrt_filesystem.h>
#endif
#endif
#include <memory>

namespace Hatchit {

    namespace Core {

        Debug::LogCallback              Debug::s_logCallback;
        std::ofstream                   Debug::s_outputStream;
        bool                            Debug::s_canLogToFile = false;
        const std::string               Debug::s_severityStrings[5] =
        {
            std::string("[DEBUG]"),
            std::string("[INFO] "),
            std::string("[WARN] "),
            std::string("[ERROR]"),
            std::string("[PERFORMANCE]")
        };
#if defined(_DEBUG) || defined(DEBUG)
        Debug::LogSeverity              Debug::s_severityThreshold = Debug::LogSeverity::Debug;
#else
        Debug::LogSeverity              Debug::s_severityThreshold = Debug::LogSeverity::Info;
#endif

        std::string Debug::CreateLogMessage(Debug::LogSeverity severity, std::string message)
        {
            return fmt::sprintf("%s %s %s", GenerateTimestamp(), s_severityStrings[static_cast<int>(severity)], message);
        }

        std::string Debug::GenerateTimestamp()
        {
            std::time_t time_epoch = std::time(nullptr);
            tm*         time_local = std::localtime(&time_epoch);

            return fmt::sprintf("[%02d:%02d:%02d]", time_local->tm_hour, time_local->tm_min, time_local->tm_sec);
        }

        std::string Debug::GetOutputFileName()
        {
#ifdef HT_WINDOWS_STORE_APP
            return WinRT::Directory::LocalFolder() + os_exec_name() + ".log";
#else
            return os_exec_dir() + os_exec_name() + ".log";
#endif
        }

        Debug::LogSeverity Debug::GetSeverityThreshold()
        {
            return s_severityThreshold;
        }

        
        void Debug::InitializeOutputStream()
        {
            bool canLog = true;

            // Open the file
            s_outputStream.open(GetOutputFileName(), std::ios::app | std::ios::binary | std::ios::out);
            if (!s_outputStream.is_open())
            {
                std::string message = CreateLogMessage(LogSeverity::Error, "Failed to open output file '" + GetOutputFileName() + "'.\n");
            
                #if defined(HT_SYS_WINDOWS)
                    OutputDebugStringA(message.c_str());
                #endif

                std::cout << message.c_str();
            }
            else
            {
                std::time_t time_epoch = std::time(nullptr);
                tm*         time_local = std::localtime(&time_epoch);
                std::string separator = fmt::sprintf(
                    "------- LOG FILE OPENED ON %02d/%02d/%d -------\n",
                    time_local->tm_mon + 1,
                    time_local->tm_mday,
                    time_local->tm_year + 1900);
                LogMessage(CreateLogMessage(LogSeverity::Info, separator));

            }
        }

        void Debug::CloseOutputStream()
        {
            if (s_outputStream.is_open())
                s_outputStream.close();
        }

        Debug & Debug::instance()
        {
            static Debug _instance;

            return _instance;
        }

        void Debug::LogMessage(const std::string& message)
        {
            // If we should try to open the file then, well, try to open it
            if (!s_outputStream.is_open())
                InitializeOutputStream();

#if defined(HT_SYS_WINDOWS)
            // Output to the Visual Studio debug window
            OutputDebugStringA(message.c_str());
#endif

            // Output to the console and file
            std::cout << message.c_str();

            if (s_outputStream.is_open())
                (s_outputStream) << message.c_str();

            // Invoke the callback
            if (s_logCallback)
            {
                s_logCallback(message);
            }
        }

        
        void Debug::SetLogCallback(LogCallback callback)
        {
            s_logCallback = callback;
        }

        void Debug::SetSeverityThreshold(Debug::LogSeverity threshold)
        {
            s_severityThreshold = threshold;
        }

        bool Debug::ShouldLogSeverity(Debug::LogSeverity severity)
        {
            return static_cast<int>(severity) >= static_cast<int>(s_severityThreshold);
        }

    }

}

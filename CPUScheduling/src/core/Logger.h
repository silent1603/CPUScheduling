#ifndef LOGGER_H
#define LOGGER_H
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
namespace CPUScheduling
{
    namespace Core
    {
        class Log
        {
        public:
            static void Init();
            static std::shared_ptr<spdlog::logger> &GetAppLogger() { return  s_AppLogger; }
        private:
            static std::shared_ptr<spdlog::logger> s_AppLogger;
        };
    }
}

#define APP_CORE_TRACE(...) ::CPUScheduling::Core::Log::GetAppLogger()->trace(__VA_ARGS__)
#define APP_CORE_INFO(...) ::CPUScheduling::Core::Log::GetAppLogger()->info(__VA_ARGS__)
#define APP_CORE_WARN(...) ::CPUScheduling::Core::Log::GetAppLogger()->warn(__VA_ARGS__)
#define APP_CORE_ERROR(...) ::CPUScheduling::Core::Log::GetAppLogger()->error(__VA_ARGS__)
#define APP_CORE_CRITICAL(...) ::CPUScheduling::Core::Log::GetAppLogger()->critical(__VA_ARGS__)


#endif
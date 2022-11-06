#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"


 std::shared_ptr<spdlog::logger> Core::Log::s_AppLogger;

 void Core::Log::Init()
{
            std::vector<spdlog::sink_ptr> logSinks;
            logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("App.log", true));

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");

            s_AppLogger = std::make_shared<spdlog::logger>("App", begin(logSinks), end(logSinks));
            spdlog::register_logger(s_AppLogger);
            s_AppLogger->set_level(spdlog::level::trace);
            s_AppLogger->flush_on(spdlog::level::trace);

}

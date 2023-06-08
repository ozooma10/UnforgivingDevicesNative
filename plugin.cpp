#include <format>
#include <thread>
#include <chrono>
#include <atomic>
#include <spdlog/sinks/basic_file_sink.h>

#include <UD_H.h>


namespace logger = SKSE::log;

#if(UDDEBUG > 1U)
void SetupLog() {
    auto logsFolder = SKSE::log::log_directory();
    if (!logsFolder) SKSE::stl::report_and_fail("SKSE log_directory not provided, logs disabled.");
    auto pluginName = SKSE::PluginDeclaration::GetSingleton()->GetName();
    auto logFilePath = *logsFolder / std::format("{}.log", pluginName);
    auto fileLoggerPtr = std::make_shared<spdlog::sinks::basic_file_sink_mt>(logFilePath.string(), true);
    auto loggerPtr = std::make_shared<spdlog::logger>("log", std::move(fileLoggerPtr));
    spdlog::set_default_logger(std::move(loggerPtr));
    spdlog::set_level(spdlog::level::trace);
    spdlog::flush_on(spdlog::level::trace);
}
#endif

SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    #if(UDDEBUG > 1U)
        SetupLog();
    #endif
    SKSE::GetPapyrusInterface()->Register(UD::RegisterPapyrusFunctions);
    SKSE::GetMessagingInterface()->RegisterListener(UD::OnMessageReceived);
    SKSE::AllocTrampoline(64);
    return true;
}
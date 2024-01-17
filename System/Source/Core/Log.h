#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace PreViewer {

	class PV_API Log
	{
	public:
		enum class Patterns
		{
			None = 0,
			Line, Simple
		};

	protected:
		explicit Log() = default;

	public:
		virtual ~Log() = default;

		static void init();
		static void setPattern(Patterns p);
		
		inline static std::shared_ptr<spdlog::logger>& GetCoreLoger()
		{
			init();
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetClientLoger()
		{
			init();
			return s_ClientLogger;
		}

	private:
		inline static bool s_Initialized = false;
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

		static Patterns s_CurrentPattern;
	};


#pragma region CoreDefines 
	// Normal Engine Core log macros
#define PV_CORE_TRACE(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->trace( __VA_ARGS__ );

#define PV_CORE_DEBUG(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->debug( __VA_ARGS__ );

#define PV_CORE_INFO(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->info( __VA_ARGS__ );

#define PV_CORE_WARN(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->warn( __VA_ARGS__ );

#define PV_CORE_ERROR(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->error( __VA_ARGS__ );

#define PV_CORE_CRITICAL(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetCoreLoger()->critical( __VA_ARGS__ );

#define PV_CORE_LINE_TRACE(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::trace, __VA_ARGS__);

#define PV_CORE_LINE_DEBUG(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::debug, __VA_ARGS__);

#define PV_CORE_LINE_INFO(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::info, __VA_ARGS__);

#define PV_CORE_LINE_WARN(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::warn, __VA_ARGS__);

#define PV_CORE_LINE_ERROR(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::err, __VA_ARGS__);

#define PV_CORE_LINE_CRITICAL(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetCoreLoger(), spdlog::level::critical, __VA_ARGS__);

#pragma endregion 

#pragma region ClientDefines 
#define PV_CLIENT_TRACE(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->trace( __VA_ARGS__ );

#define PV_CLIENT_DEBUG(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->debug( __VA_ARGS__ );

#define PV_CLIENT_INFO(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->info( __VA_ARGS__ );

#define PV_CLIENT_WARN(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->warn( __VA_ARGS__ );

#define PV_CLIENT_ERROR(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->error( __VA_ARGS__ );

#define PV_CLIENT_CRITICAL(...) \
    Log::setPattern( Log::Patterns::Simple ); \
    PreViewer::Log::GetClientLoger()->critical( __VA_ARGS__ );

#define PV_CLIENT_LINE_TRACE(...)    \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::trace, __VA_ARGS__);

#define PV_CLIENT_LINE_DEBUG(...)    \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::debug, __VA_ARGS__);

#define PV_CLIENT_LINE_INFO(...)     \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::info, __VA_ARGS__);

#define PV_CLIENT_LINE_WARN(...)     \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::warn, __VA_ARGS__);

#define PV_CLIENT_LINE_ERROR(...)    \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::err, __VA_ARGS__);

#define PV_CLIENT_LINE_CRITICAL(...) \
    Log::setPattern( Log::Patterns::Line ); \
    SPDLOG_LOGGER_CALL( PreViewer::Log::GetClientLoger(), spdlog::level::critical, __VA_ARGS__);

// This macro should be defined to use NR_SET_NAME
#pragma endregion 

} // namespace PreViewer
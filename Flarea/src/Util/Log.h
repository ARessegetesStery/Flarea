#ifndef _LOG_H
#define _LOG_H

#include "flrpch.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace FLR
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }
	private:
		inline static std::shared_ptr<spdlog::logger> coreLogger;
		inline static std::shared_ptr<spdlog::logger> clientLogger;
	};

}

#ifndef FLR_RELEASE

// Core log macros
#define FLR_CORE_TRACE(...)     ::FLR::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FLR_CORE_INFO(...)      ::FLR::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FLR_CORE_WARN(...)      ::FLR::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FLR_CORE_ERROR(...)     ::FLR::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FLR_CORE_CRITICAL(...)  ::FLR::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define FLR_CORE_FATAL(...)	    ::FLR::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define FLR_TRACE(...)		    ::FLR::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FLR_INFO(...)		    ::FLR::Log::GetClientLogger()->info(__VA_ARGS__)
#define FLR_WARN(...)		    ::FLR::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FLR_ERROR(...)		    ::FLR::Log::GetClientLogger()->error(__VA_ARGS__)
#define FLR_CRITICAL(...)	    ::FLR::Log::GetClientLogger()->critical(__VA_ARGS__)
#define FLR_FATAL(...)		    ::FLR::Log::GetClientLogger()->fatal(__VA_ARGS__)

#else

// Core log macros
#define FLR_CORE_TRACE(...)
#define FLR_CORE_INFO(...)
#define FLR_CORE_WARN(...)
#define FLR_CORE_ERROR(...)
#define FLR_CORE_CRITICAL(...)
#define FLR_CORE_FATAL(...)

// Client log macros
#define FLR_TRACE(...)
#define FLR_INFO(...)
#define FLR_WARN(...)
#define FLR_ERROR(...)
#define FLR_CRITICAL(...)
#define FLR_FATAL(...)
#endif

#endif

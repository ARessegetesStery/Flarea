#include "flrpch.h"
#include "Log.h"

namespace FLR
{
	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		coreLogger = spdlog::stdout_color_mt("Flarea");
		coreLogger->set_level(spdlog::level::trace);

		clientLogger = spdlog::stdout_color_mt("Client");
		clientLogger->set_level(spdlog::level::trace);
	}

}

#include "mspch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Mystic {

	std::shared_ptr<spdlog::logger> Log::_coreLogger;
	std::shared_ptr<spdlog::logger> Log::_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		_coreLogger = spdlog::stdout_color_mt("MYSTIC");
		_coreLogger->set_level(spdlog::level::trace);

		_clientLogger = spdlog::stdout_color_mt("APP");
		_clientLogger->set_level(spdlog::level::trace);
	}

}

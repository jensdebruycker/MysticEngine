#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Mystic {

	class MYSTIC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return _coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return _clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> _coreLogger;
		static std::shared_ptr<spdlog::logger> _clientLogger;
	};

}

//Core log macros
#define MS_CORE_TRACE(...)   ::Mystic::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MS_CORE_INFO(...)    ::Mystic::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MS_CORE_WARN(...)    ::Mystic::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MS_CORE_ERROR(...)   ::Mystic::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MS_CORE_FATAL(...)   ::Mystic::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define MS_TRACE(...)   ::Mystic::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MS_INFO(...)    ::Mystic::Log::GetClientLogger()->info(__VA_ARGS__)
#define MS_WARN(...)    ::Mystic::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MS_ERROR(...)   ::Mystic::Log::GetClientLogger()->error(__VA_ARGS__)
#define MS_FATAL(...)   ::Mystic::Log::GetClientLogger()->fatal(__VA_ARGS__)

#pragma once

#ifdef MS_PLATFORM_WINDOWS
	#ifdef MS_BUILD_DLL
		#define MYSTIC_API __declspec(dllexport)
	#else
		#define MYSTIC_API __declspec(dllimport)
	#endif
#else
	#error MysticEngine only supports windows!
#endif

#ifdef MS_ENABLE_ASSERTS
	#define MS_ASSERT(x, ...) { if(!(x)) { MS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MS_CORE_ASSERT(x, ...) { if(!(x)) { MS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MS_ASSERT(...)
	#define MS_CORE_ASSERT(...)
#endif

#define BIT(x) (1 << x)

#define MS_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)